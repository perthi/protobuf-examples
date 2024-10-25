// -*- mode: c++ -*-
#pragma once


#include <utilities/GEnum.h>

G_ENUM( eXML_NODETYPE,
{
	EOpenTagNode, 
    ECloseTagNode, 
    ESingleTagNode, 
    ETextNode, 
    ECommentNode, 
    EProcInstrNode, 
    EDocTypeNode, 
    ECDataNode
})
