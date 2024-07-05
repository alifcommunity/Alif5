#include "alif.h"

#include "AlifCore_AST.h"
#include "AlifCore_Compile.h"
#include "AlifCore_Interpreter.h"
#include "AlifCore_Object.h"
#include "AlifCore_AlifCycle.h"
#include "AlifCore_AlifState.h"
#include "AlifParserEngine.h"
//#include "AlifCore_AlifRun.h"

#ifdef _WINDOWS
#include "windows.h"
#endif // _WINDOWS


// Forward Declaration
//static AlifObject* alifRun_file(FILE*, AlifObject*, int, int);
//Module* alifParser_astFromFile(FILE*, AlifObject*, int, AlifASTMem*); // temp


static AlifObject* run_evalCodeObject(AlifThread* _thread, AlifCodeObject* _co, AlifObject* _globals, AlifObject* _locals) { // 1258
	AlifObject* val{};

	AlifIntT hasBuiltins = alifDict_containsString(_globals, L"__builtins__");
	if (hasBuiltins < 0) return nullptr;

	//if (!hasBuiltins) {
	//	if (alifDict_setItemString(_globals, L"__builtins__", _thread->interpreter->builtins)) {
	//		return nullptr;
	//	}
	//}

	val = alifEval_evalCode((AlifObject*)_co, _globals, _locals);
	// error
	return val;
}

static AlifObject* alifRun_module(Module* _module, AlifObject* _fn, AlifObject* _globals, AlifObject* _locals,  AlifASTMem* _astMem) { // 1299

	AlifThread* thread_ = alifThread_get();

	AlifCodeObject* codeObj = alifAST_compile(_module, _fn, -1, _astMem);
	if (codeObj == nullptr) {
		// error
		return nullptr;
	}


	AlifObject* exec = run_evalCodeObject(thread_, codeObj, _globals, _locals);
	ALIF_DECREF(codeObj);
	return exec;
}


static AlifObject* alifRun_file(FILE* _fp, AlifObject* _fn, int _start,AlifObject* _globals, AlifObject* _locals,  int _fClose) { 

	AlifASTMem* astMem = alifASTMem_new();

	Module* module_{};
	module_ = alifParser_astFromFile(_fp, _fn, _start, astMem);

	if (_fClose) {
		fclose(_fp);
	}

	AlifObject* res_{};
	if (module_) {
		res_ = alifRun_module(module_, _fn, _globals, _locals, astMem);
	}
	else {
		res_ = nullptr;
	}


	return res_;
}

int alifRun_simpleFileObj(FILE* _fp, AlifObject* _fn, int _fClose) {

	AlifObject* mainModule = alifImport_addModuleRef(L"__main__");
	if (mainModule == NULL)
		return -1;
	AlifObject* dict_ = alifModule_getDict(mainModule);  // borrowed ref

	int set_file_name = 0;
	int has_file = alifDict_containsString(dict_, L"__file__");
	if (has_file < 0) {
		//goto done;
	}

	int exitcode = -1;

	AlifObject* mod{};

	mod = alifRun_file(_fp, _fn, ALIFFILE_INPUT,dict_, dict_, _fClose);
	if (mod == nullptr) {
		goto done;
	}

	ALIF_DECREF(mod); // يجب إصلاح دالة الحذف داخل هذا المتغير الاسمي
	exitcode = 0;

done:
	return exitcode;
}

int alifRun_fileObj(FILE* _fp, AlifObject* _fn, int _fClose) { 

	int res{};



	if (_isatty(_fileno(_fp))) { // هذا يعني انه تفاعلي
		//res_ = alifRun_interactiveLoop(_fp, _fn);
		if (_fClose) {
			fclose(_fp);
		}
	}
	else {
		res = alifRun_simpleFileObj(_fp, _fn, _fClose);
	}

	return res;
}


