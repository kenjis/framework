
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "ext/spl/spl_exceptions.h"


/**
 * In validator.
 *
 * @package     Ice/Validation
 * @category    Security
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Validation_Validator_In) {

	ZEPHIR_REGISTER_CLASS_EX(Ice\\Validation\\Validator, In, ice, validation_validator_in, ice_validation_validator_ce, ice_validation_validator_in_method_entry, 0);

	return SUCCESS;

}

/**
 * Validate the validator
 *
 * @param Validation validation
 * @param string field
 * @return boolean
 */
PHP_METHOD(Ice_Validation_Validator_In, validate) {

	zephir_nts_static zephir_fcall_cache_entry *_10 = NULL;
	zend_bool _0, _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *field = NULL;
	zval *validation, *field_param = NULL, *value = NULL, *label = NULL, *message = NULL, *i18n = NULL, *replace, *values = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &validation, &field_param);

	if (unlikely(Z_TYPE_P(field_param) != IS_STRING && Z_TYPE_P(field_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'field' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(field_param) == IS_STRING)) {
		zephir_get_strval(field, field_param);
	} else {
		ZEPHIR_INIT_VAR(field);
		ZVAL_EMPTY_STRING(field);
	}


	ZEPHIR_CALL_METHOD(&value, validation, "getvalue", NULL, field);
	zephir_check_call_status();
	_0 = ZEPHIR_IS_STRING_IDENTICAL(value, "");
	if (!(_0)) {
		_0 = Z_TYPE_P(value) == IS_NULL;
	}
	if (_0) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 1);
	ZEPHIR_CALL_METHOD(&values, this_ptr, "getoptions", NULL, _1);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(values)) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "values", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&values, this_ptr, "get", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(values) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(ice_exception_ce, "Values must be an array", "ice/validation/validator/in.zep", 44);
		return;
	}
	if (!(zephir_fast_in_array(value, values TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "label", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "has", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		if (zephir_is_true(_2)) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "label", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&label, this_ptr, "get", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&label, validation, "getlabel", NULL, field);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "message", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "has", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		if (zephir_is_true(_3)) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "message", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&message, this_ptr, "get", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "in", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&message, validation, "getdefaultmessage", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&_4, validation, "gettranslate", NULL);
		zephir_check_call_status();
		_5 = ZEPHIR_IS_TRUE_IDENTICAL(_4);
		if (_5) {
			ZEPHIR_CALL_METHOD(&_6, validation, "getdi", NULL);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "i18n", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&_7, _6, "has", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			_5 = zephir_is_true(_7);
		}
		if (_5) {
			ZEPHIR_CALL_METHOD(&_8, validation, "getdi", NULL);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "i18n", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&i18n, _8, "get", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_9, i18n, "translate", NULL, label);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(label, _9);
			ZEPHIR_CALL_METHOD(&_9, i18n, "translate", NULL, message);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(message, _9);
		}
		ZEPHIR_INIT_VAR(replace);
		zephir_create_array(replace, 2, 0 TSRMLS_CC);
		zephir_array_update_string(&replace, SL(":field"), &label, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_1);
		zephir_fast_join_str(_1, SL(", "), values TSRMLS_CC);
		zephir_array_update_string(&replace, SL(":values"), &_1, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_8, "strtr", &_10, message, replace);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, validation, "addmessage", NULL, field, _8);
		zephir_check_call_status();
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

