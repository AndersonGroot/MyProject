#include "stdafx.h"
#include "Student.h"


CStudent::CStudent(unsigned int id, CMyString name, unsigned int year, unsigned int month, char sex, bool IsExist, unsigned int offset)
:IsExist_(IsExist), id_(id), name_(name), year_(year), month_(month), sex_(sex), offset_(offset)
{
}

//øΩ±¥ππ‘Ï
CStudent::CStudent(const CStudent& obj)
{
    IsExist_ = obj.IsExist_;
    offset_ = obj.offset_;
    Length_ = obj.Length_;
    id_ = obj.id_;
    name_ = obj.name_;
    year_ = obj.year_;
    month_ = obj.month_;
    sex_ = obj.sex_;
}

CStudent::~CStudent()
{
}
