#pragma once
#include "IWorker.h"
#include "CPersonImpl.h"

class CWorker : public CPersonImpl<IWorker>
{
public:

	CWorker() = default;

};