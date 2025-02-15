
namespace Ice\Auth\Social;

/**
 * Twitter Auth social adapter.
 *
 * @package     Ice/Auth
 * @category    Adapter
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 */
class Twitter extends Adapter
{

    /**
     * Twitter adapter constructor.
     *
     * @param array config
     */
    public function __construct(config = [])
    {
        let this->_provider = "twitter";

        parent::__construct(config);

        let this->_socialFieldsMap = [
                "socialId": "id",
                "email":    "email",
                "name":     "name",
                "sex":      "sex",
                "birthday": "bdate"
            ],
            this->_responseType = "oauth_token";
    }

    /**
     * Get user social id or null if it is not set.
     *
     * @return string|null
     */
    public function getSocialPage()
    {
        if this->has("screen_name") {
            return "http://twitter.com/" . this->get("screen_name");
        }

        return null;
    }

    /**
     * Get url of user"s avatar or null if it is not set.
     *
     * @return string|null
     */
    public function getImage()
    {
        if this->has("profile_image_url") {
            return implode("", explode("_normal", this->get("profile_image_url")));
        }

        return null;
    }

    /**
     * Authenticate and return bool result of authentication.
     *
     * @return bool
     */
    public function authenticate()
    {
        var result, params, accessTokenUrl, accessTokens, getDataUrl, userInfo;

        let result = false;

        if isset _GET["oauth_token"] && isset _GET["oauth_verifier"] {
            let params = [
                "oauth_token":    _GET["oauth_token"],
                "oauth_verifier": _GET["oauth_verifier"]
            ];

            let accessTokenUrl = "https://api.twitter.com/oauth/access_token",
                params = this->prepareUrlParams(accessTokenUrl, params),
                accessTokens = this->call(parent::GET, accessTokenUrl, params, false);

            parse_str(accessTokens, accessTokens);

            if isset accessTokens["oauth_token"] {
                let getDataUrl = "https://api.twitter.com/1.1/users/show.json",
                    params = [
                        "oauth_token":      accessTokens["oauth_token"],
                        "screen_name":      accessTokens["screen_name"],
                        "include_entities": "false"
                    ],
                    params = this->prepareUrlParams(getDataUrl, params, accessTokens["oauth_token_secret"]),
                    userInfo = this->call(parent::GET, getDataUrl, params);

                if isset userInfo["id"] {
                    let this->_userInfo = userInfo,
                        result = true;
                }
            }
        }
        return result;
    }

    /**
     * Prepare params for authentication url.
     *
     * @return array
     */
    public function prepareAuthParams()
    {
        var requestTokenUrl, requestTokens, params;

        let requestTokenUrl = "https://api.twitter.com/oauth/request_token",
            params = this->prepareUrlParams(requestTokenUrl, ["oauth_callback": this->_redirectUri]),
            requestTokens = this->call(parent::GET, requestTokenUrl, params, false);

        parse_str(requestTokens, requestTokens);

        return [
            "auth_url": "https://api.twitter.com/oauth/authenticate",
            "auth_params": ["oauth_token": (isset requestTokens["oauth_token"] ? requestTokens["oauth_token"] : null)]
        ];
    }

    /**
     * Prepare url-params with signature.
     *
     * @return array
     */
    private function prepareUrlParams(string url, params = [], string oauthToken = "", string type = "GET") 
    {
        var sigBaseStr, key;

        let params = array_merge([
            "oauth_consumer_key":     this->_clientId,
            "oauth_nonce":            md5(uniqid(rand(), true)),
            "oauth_signature_method": "HMAC-SHA1",
            "oauth_timestamp":        time(),
            "oauth_token":            oauthToken,
            "oauth_version":          "1.0"
        ], params);

        ksort(params);

        let sigBaseStr = type . "&" . urlencode(url) . "&" . urlencode(http_build_query(params)),
            key = this->_clientSecret . "&" . oauthToken,
            params["oauth_signature"] = base64_encode(hash_hmac("sha1", sigBaseStr, key, true)),
            params = array_map("urlencode", params);

        return params;
    }
}
