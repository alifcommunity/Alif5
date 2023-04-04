#include "Compiler.h"


Compiler::Compiler(std::vector<ExprNode*>* _statements, MemoryBlock* _alifMemory) :
	statements_(_statements), alifMemory(_alifMemory) {}

void Compiler::compile_file() 
{
	for (ExprNode* node_ : *statements_)
	{
		VISIT_(exprs, node_); // تم شرح طريقة الاستدعاء في ملف compiler.h
	}
}


AlifObject* Compiler::visit_object(ExprNode* _node)
{
	instructions_.push_back(SET_DATA);
	data_.push_back(_node->U.Object.value_);
	return _node->U.Object.value_;
}


AlifObject* Compiler::visit_unaryOp(ExprNode* _node)
{
	AlifObject* right = VISIT_(exprs, _node->U.UnaryOp.right_);

	if (_node->U.UnaryOp.operator_ == TTMinus)
	{
		instructions_.push_back(MINUS_NUM);
	}
	else if (_node->U.UnaryOp.operator_ == TTPlus)
	{
		instructions_.push_back(PLUS_NUM);
	}
	else if (!wcscmp(_node->U.UnaryOp.keyword_, L"ليس"))
	{
		instructions_.push_back(NOT_LOGIC);
	}

	return right;
}


AlifObject* Compiler::visit_binOp(ExprNode* _node)
{
	AlifObject* right = VISIT_(exprs, _node->U.BinaryOp.right_);
	AlifObject* left = VISIT_(exprs, _node->U.BinaryOp.left_);

	if (_node->U.BinaryOp.operator_ == TTPlus)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(ADD_NUM);
			}
			else
			{
				// TypeError: int and other
			}
		}
		else if (left->objType == OTString)
		{
			if (right->objType == OTString)
			{
				instructions_.push_back(ADD_STR);
			}
			else
			{
				// TypeError: str and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTMinus)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(MINUS_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTPower)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(POW_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTDivide)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(DIV_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTMultiply)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(MUL_NUM);
			}
			else if (right->objType == OTString)
			{
				instructions_.push_back(MUL_STR);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else if (left->objType == OTString)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(MUL_STR);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTRemain)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(REM_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTEqualEqual)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(EQEQ_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTNotEqual)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(NOTEQ_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTGreaterThan)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(GRTHAN_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTLessThan)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(LSTHAN_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTGreaterThanEqual)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(GRTHANEQ_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (_node->U.BinaryOp.operator_ == TTLessThanEqual)
	{
		if (left->objType == OTNumber)
		{
			if (right->objType == OTNumber)
			{
				instructions_.push_back(LSTHANEQ_NUM);
			}
			else
			{
				// TypeError: this and other
			}
		}
		else
		{
			// TypeError: this and other
		}
	}
	else if (!wcscmp(_node->U.UnaryOp.keyword_, L"و"))
	{
		instructions_.push_back(AND_LOGIC);
	}
	else if (!wcscmp(_node->U.UnaryOp.keyword_, L"او"))
	{
		instructions_.push_back(OR_LOGIC);
	}

	return left;
}


void Compiler::visit_assign(ExprNode* _node)
{
	for (AlifObject* i : *_node->U.NameAssign.name_)
	{
		VISIT_(exprs,_node->U.NameAssign.value_);

		data_.push_back(i);
		instructions_.push_back(SET_DATA); // خزن الاسم في المكدس

		instructions_.push_back(STORE_NAME);
	}
}

void Compiler::visit_augAssign(ExprNode* _node)
{
	VISIT_(exprs, _node->U.AugNameAssign.value_);

	data_.push_back(_node->U.AugNameAssign.name_);
	instructions_.push_back(SET_DATA);

	switch (_node->U.AugNameAssign.operator_)
	{
	case TTPlusEqual:
		instructions_.push_back(AUGADD_NUM);
		break;
	case TTMinusEqual:
		instructions_.push_back(AUGSUB_NUM);
		break;
	case TTMultiplyEqual:
		instructions_.push_back(AUGMUL_NUM);
		break;
	case TTDivideEqual:
		instructions_.push_back(AUGDIV_NUM);
		break;
	case TTRemainEqual:
		instructions_.push_back(AUGREM_NUM);
		break;
	case TTPowerEqual:
		instructions_.push_back(AUGPOW_NUM);
		break;
	default:
		break;
	}
}

void Compiler::visit_access(ExprNode* _node)
{
	data_.push_back(_node->U.NameAccess.name_);
	instructions_.push_back(SET_DATA);

	instructions_.push_back(GET_DATA);
}


void Compiler::visit_expr(ExprNode* _node)
{
	VISIT_(exprs, _node->U.Expr.expr_);
	VISIT_(exprs, _node->U.Expr.elseExpr);
	VISIT_(exprs, _node->U.Expr.condetion_);

	instructions_.push_back(EXPR_OP);
}

void Compiler::visit_list(ExprNode* _node)
{
	// إسناد العناصر التي سيتم إعدادها
	for (ExprNode* element : *_node->U.Object.value_->V.ListObj.list_)
	{
		VISIT_(exprs, element);
	}


	// لتحديد نهاية المصفوفة في المفسر
	AlifObject* listEnd = (AlifObject*)alifMemory->allocate(sizeof(AlifObject));
	listEnd->objType = OTNumber;
	listEnd->V.NumberObj.numberValue = _node->U.Object.value_->V.ListObj.list_->size();

	data_.push_back(listEnd);
	instructions_.push_back(SET_DATA);


	// تعريف المصفوفة التي ستحتوي على العناصر التي تم إعداداها
	AlifObject* listObj = (AlifObject*)alifMemory->allocate(sizeof(AlifObject));
	std::vector<AlifObject*>* elements_ = new std::vector<AlifObject*>;

	listObj->objType = OTList;
	listObj->V.ListObj.objList = elements_;

	data_.push_back(listObj);
	instructions_.push_back(SET_DATA);



	instructions_.push_back(LIST_MAKE);
}


AlifObject* Compiler::visit_exprs(ExprNode* _node)
{
	if (_node->type_ == VTObject)
	{
		return VISIT_(object, _node);
	}
	else if (_node->type_ == VTUnaryOp)
	{
		VISIT_(unaryOp, _node);
	}
	else if (_node->type_ == VTBinOp)
	{
		return VISIT_(binOp,_node);
	}
	else if (_node->type_ == VTAssign)
    {
		VISIT_(assign,_node);
    }
	else if (_node->type_ == VTAugAssign)
	{
		VISIT_(augAssign, _node);
	}
	else if (_node->type_ == VTAccess)
	{
		VISIT_(access, _node);
	}
	else if (_node->type_ == VTExpr)
    {
		VISIT_(expr, _node);
    }
	else if (_node->type_ == VTList)
	{
		VISIT_(list, _node);
	}
}

AlifObject* Compiler::visit_stmts(StmtsNode* _node)
{
	return nullptr;
}