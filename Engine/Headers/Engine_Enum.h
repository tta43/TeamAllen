/*!
 * \file Engine_Enum.h
 * \date 2015/05/01 15:57
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	//! @ brief ���� ��ȯ�ɶ� �������� ���ҽ��� �����ؾ��� ���ҽ��� ������.
	enum RESOURCETYPE
	{
		RESOURCE_STATIC,	//!< �����ؾ� �� ���ҽ�
		RESOURCE_DYNAMIC,	//!< ������ �� ���ҽ�
		RESOURCE_END,
	};

	enum TEXTURETYPE
	{
		TEXTURE_NORMAL,
		TEXTURE_CUBE,
		TEXTURE_END,
	};

	enum BUFFERTYPE
	{
		BUFFER_TRICOLOR,
		BUFFER_RCCOLOR,
		BUFFER_RCTEX,
		BUFFER_CUBETEX,
		BUFFER_TERRAINTEX,
		BUFFER_WALLTEX,
		BUFFER_WALLXYTEX,
	};

	enum ANGLE {ANGLE_X, ANGLE_Y, ANGLE_Z, ANGLE_END,};
}

#endif // Engine_Enum_h__