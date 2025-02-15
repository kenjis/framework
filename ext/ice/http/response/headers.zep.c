
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/iterator.h"
#include "kernel/concat.h"


/**
 * This class is a bag to manage the response headers.
 *
 * @package     Ice/Http
 * @category    Component
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Http_Response_Headers) {

	ZEPHIR_REGISTER_CLASS_EX(Ice\\Http\\Response, Headers, ice, http_response_headers, ice_arr_ce, ice_http_response_headers_method_entry, 0);

	zend_class_implements(ice_http_response_headers_ce TSRMLS_CC, 1, ice_http_response_headersinterface_ce);
	return SUCCESS;

}

/**
 * Sends the headers to the client.
 *
 * @return boolean
 */
PHP_METHOD(Ice_Http_Response_Headers, send) {

	zend_object_iterator *_2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_4 = NULL;
	zval *header = NULL, *value = NULL, *_0 = NULL, *_3 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&_0, "headers_sent", &_1);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		_2 = zephir_get_iterator(this_ptr TSRMLS_CC);
		_2->funcs->rewind(_2 TSRMLS_CC);
		for (;_2->funcs->valid(_2 TSRMLS_CC) == SUCCESS && !EG(exception); _2->funcs->move_forward(_2 TSRMLS_CC)) {
			ZEPHIR_GET_IMKEY(header, _2);
			{
				zval **ZEPHIR_TMP_ITERATOR_PTR;
				_2->funcs->get_current_data(_2, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
				ZEPHIR_CPY_WRT(value, (*ZEPHIR_TMP_ITERATOR_PTR));
			}
			if (!(ZEPHIR_IS_EMPTY(value))) {
				ZEPHIR_INIT_LNVAR(_3);
				ZEPHIR_CONCAT_VSV(_3, header, ": ", value);
				ZEPHIR_CALL_FUNCTION(NULL, "header", &_4, _3, ZEPHIR_GLOBAL(global_true));
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_FUNCTION(NULL, "header", &_4, header, ZEPHIR_GLOBAL(global_true));
				zephir_check_call_status();
			}
		}
		_2->funcs->dtor(_2 TSRMLS_CC);
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

