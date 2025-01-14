
namespace Ice;

use Ice\Validation\Validator;

/**
 * Allows to validate array data.
 *
 * @package     Ice/Validation
 * @category    Security
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 * @uses        Ice\Filter (if service is available)
 * @uses        Ice\I18n (if service is available)
 */
class Validation
{

    protected _di { get };
    protected _data = [];
    protected _rules = [] { set };
    protected _validators = [];
    protected _filters = [] { set };
    protected _labels = [] { set };
    protected _messages = [];
    protected _valid = true;
    protected _aliases = [] { set };
    protected _translate = true { set, get };
    protected _humanLabels = false { set };
    protected _defaultMessages = [
        "alnum": "Field :field must contain only letters and numbers",
        "alpha": "Field :field must contain only letters",
        "between": "Field :field must be within the range of :min to :max",
        "digit": "Field :field must be numeric",
        "default": "Field :field is not valid",
        "email": "Field :field must be an email address",
        "fileEmpty": "Field :field must not be empty",
        "fileIniSize": "File :field exceeds the maximum file size",
        "fileMaxResolution": "File :field must not exceed :max resolution",
        "fileMinResolution": "File :field must be at least :min resolution",
        "fileSize": "File :field exceeds the size of :max",
        "fileType": "File :field must be of type: :types",
        "in": "Field :field must be a part of list: :values",
        "lengthMax": "Field :field must not exceed :max characters long",
        "lengthMin": "Field :field must be at least :min characters long",
        "notIn": "Field :field must not be a part of list: :values",
        "regex": "Field :field does not match the required format",
        "required": "Field :field is required",
        "same": "Field :field and :other must match",
        "unique": "Field :field must be unique",
        "url": "Field :field must be a url",
        "with": "Field :field must occur together with :fields",
        "without": "Field :field must not occur together with :fields"
    ];

    /**
     * Validation constructor. Fetch Di and set the data if given.
     *
     * @param array data Data to validate
     */
    public function __construct(array data = [])
    {
        let this->_di = Di::$fetch(),
            this->_data = data;
    }

    /**
     * Resolve one rule.
     *
     * @param string alias
     * @param string field
     * @param mixed options
     * @return void
     */
    public function resolve(string alias, string field, var options = null) -> void
    {
        var rule;

        if !fetch rule, this->_aliases[alias] {
            let rule = "Ice\\Validation\\Validator\\" . camelize(alias);

            if !class_exists(rule) {
                throw new Exception(sprintf("Validator %s not found", alias));
            }
        }

        let this->_rules[field][] = <Validator> create_instance_params(rule, [options]);
    }

    /**
     * Add one rule.
     *
     * @param string field
     * @param mixed validators
     * @param mixed options
     * @return void
     */
    public function rule(string field, var validators, var options = null) -> void
    {
        var validator, rules, rule, alias, values;

        switch typeof validators {
            case "object":
                let this->_rules[field][] = <Validator> validators;
            break;
            case "array":
                for validator, options in validators {
                    if typeof validator == "integer" {
                        let validator = options;
                    }
                    this->rule(field, validator, options);
                }
            break;
            case "string":
                if strpos(validators, "|") === false && strpos(validators, ":") === false {
                    this->resolve(validators, field, options);
                } else {
                    let rules = explode("|", validators);

                    for rule in rules {
                        let options = explode(":", rule),
                            alias = array_shift(options);

                        if alias != "regex" {
                            if fetch values, options[0] {
                                let options = explode(",", values);
                            }
                        }

                        this->resolve(alias, field, options);
                    }
                }
            break;
        }
    }

    /**
     * Add multiple rules at once.
     *
     * @param array validators
     * @return void
     */
    public function rules(array! validators) -> void
    {
        var field, rules;

        for field, rules in validators {
            this->rule(field, rules);
        }
    }

    /**
     * Validate the data.
     *
     * @param array data Data to validate
     * @return boolean
     */
    public function validate(array data = []) -> boolean
    {
        var field, rules, rule;

        if count(data) {
            let this->_data = data;
        }

        // Validate the rules
        for field, rules in this->_rules {
            for rule in rules {
                if rule->validate(this, field)  === false {
                    let this->_valid = false;
                }
            }
        }

        // Double check
        if count(this->_messages) {
            let this->_valid = false;
        }

        return this->_valid;
    }

    /**
     * Check if validation passed.
     *
     * @return boolean
     */
    public function valid() -> boolean
    {
        return this->_valid;
    }

    /**
     * Whether or not a value exists by field.
     *
     * @param string field The data key
     * @return boolean
     */
    public function hasValue(string! field) -> boolean
    {
        return isset this->_data[field];
    }

    /**
     * Get a value by field.
     *
     * @param string field The data key
     * @param boolean filtered Get the filtered value or original
     * @return mixed
     */
    public function getValue(string! field, boolean filtered = true)
    {
        var value, filters;

        fetch value, this->_data[field];

        // Filter the value
        if filtered && this->_di->has("filter") && fetch filters, this->_filters[field] {
            let value = this->_di->get("filter")->sanitize(value, filters);
        }

        return value;
    }

    /**
     * Get the label of a field.
     * Humanize a label if humanLabels attribute and filter service is available
     *
     * @param string field The data key
     * @return string
     */
    public function getLabel(string! field) -> string
    {
        var label;

        if !fetch label, this->_labels[field] {
            // Humanize the field
            if this->_humanLabels && this->_di->has("filter") {
                let label = this->_di->get("filter")->sanitize(field, "human");
            } else {
                let label = field;
            }
        }

        return label;
    }

    /**
     * Set the default messages.
     *
     * @param array messages
     * @return void
     */
    public function setDefaultMessages(array messages = []) -> void
    {
        let this->_defaultMessages = array_merge(this->_defaultMessages, messages);
    }

    /**
     * Get a default message for the type.
     *
     * @param string type Type of message
     * @return string
     */
    public function getDefaultMessage(string! type) -> string
    {
        var message;

        if !fetch message, this->_defaultMessages[type] {
            let message = this->_defaultMessages["default"];
        }

        return message;
    }

    /**
     * Add a message to the field.
     *
     * @param string field
     * @param string message
     * @return void
     */
    public function addMessage(string! field, string message) -> void
    {
        let this->_messages[field][] = message;
    }

    /**
     * Get the validation's messages.
     *
     * @return Arr
     */
    public function getMessages() -> <Arr>
    {
        return new Arr(this->_messages);
    }
}
