/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Tristan Porteries.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file gameengine/Expressions/PythonValue.cpp
 *  \ingroup expressions
 */

#include "EXP_PythonValue.h"

EXP_PythonValue::EXP_PythonValue(PyObject *object)
	:m_value(object)
{
	Py_INCREF(m_value);
}

EXP_PythonValue::~EXP_PythonValue()
{
	Py_DECREF(m_value);
}

std::string EXP_PythonValue::GetText() const
{
	return _PyUnicode_AsString(PyObject_Repr(m_value));
}

EXP_PropValue::DATA_TYPE EXP_PythonValue::GetValueType() const
{
	return TYPE_PYTHON;
}

EXP_PropValue *EXP_PythonValue::GetReplica()
{
	EXP_PythonValue *replica = new EXP_PythonValue(*this);
	replica->ProcessReplica();

	return replica;
}

void EXP_PythonValue::ProcessReplica()
{
	Py_INCREF(m_value);
}

PyObject *EXP_PythonValue::GetValue() const
{
	return m_value;
}

PyObject *EXP_PythonValue::ConvertValueToPython()
{
	Py_INCREF(m_value);
	return m_value;
}
