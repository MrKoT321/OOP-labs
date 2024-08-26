#pragma once
#include "IAdvancedStudent.h"
#include "CStudentImpl.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{

};