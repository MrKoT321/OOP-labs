#pragma once
#include "IStudent.h"
#include "CStudentImpl.h"

class CStudent : public CStudentImpl<IStudent>
{

};