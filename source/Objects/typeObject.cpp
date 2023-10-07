

#include "alif.h"
//#include "alifCore_abstract.h"   
//#include "alifCore_call.h"          
#include "alifCore_code.h"   
//#include "alifCore_dict.h"      
//#include "alifCore_frame.h"  
//#include "alifCore_long.h"  
//#include "alifCore_memoryObject.h
//#include "alifCore_modSupport.h" 
//#include "alifCore_moduleObject.h"  
#include "alifCore_object.h"   
//#include "alifCore_alifErrors.h"  
#include "alifCore_alifState.h"    
//#include "alifCore_symTable.h"   
#include "alifCore_typeObject.h"  
//#include "alifCore_unionObject.h"  
//#include "alifCore_weakRef.h"    
//#include "opCode.h"     

#include <stddef.h>          
























































































































































































































































































































































































































































































































































































































































void alifType_initCache(AlifInterpreterState* _interp)
{
	class TypeCache* cache = &_interp->types.typeCache;
	for (AlifSizeT i = 0; i < (1 << MCACHE_SIZE_EXP); i++) {
		class TypeCacheEntry* entry = &cache->hashTable[i];
		//assert(entry->name == nullptr);

		entry->version = 0;


		//entry->name = AlifNone;
		entry->value = nullptr;
	}
}
