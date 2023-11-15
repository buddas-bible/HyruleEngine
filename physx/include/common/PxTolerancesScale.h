// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2023 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef PX_TOLERANCES_SCALE_H
#define PX_TOLERANCES_SCALE_H

/** \addtogroup common
  @{
*/

#include "common/PxPhysXCommonConfig.h"

#if !PX_DOXYGEN
namespace physx
{
#endif

/**
\brief �ùķ��̼��� ����Ǵ� �������� �����ϴ� Ŭ�����Դϴ�.
��κ��� �ùķ��̼� ��� ������ ���⿡ ���ǵ� ���� ���� ���˴ϴ�.

\note �ùķ��̼� �������� �����ϴ� ���, ����� �߷��� �⺻���� �����Ϸ��� �� ���̸�,
������ �ùķ��̼��� ���ؼ��� ����� bounceThreshold�� �����ؾ� �� ���Դϴ�.
*/

class PxTolerancesScale
{
public: 

	/**
	\brief �ùķ��̼� ���� ��ü�� �뷫���� ũ���Դϴ�.

	���� ������ �뷫 �ΰ� ũ�⸦ �ùķ��̼��ϴ� ���, 1�� ���� �����Դϴ�.
	���� ��Ƽ���� ������ �ùķ��̼��� �����ϴ� ���, 
	��� 100�� ����Ͻʽÿ�. �� ���� Ư�� ���� ���� ��� ������ �����ϴ� �� ���˴ϴ�.
	*/
	PxReal	length;

	/**
	\brief �ùķ��̼� ���� ��ü�� �Ϲ����� �ӵ� ũ���Դϴ�.
	�� ���� �浹�� ƨ�� �Ǵ� ������ ó���Ǿ�� �ϴ����� �Ǵ��ϰ�,
	�ùķ��̼ǿ��� ��ü�� ���� ���·� ��ȯ�� �� ���˴ϴ�.

	�Ϲ����� ������ ȯ�濡�� ���� ������ �߷¿� ���� 1�� ���� �������� ��ü�� �ٻ� �ӵ��Դϴ�.
	*/
	PxReal	speed;

	/**
	\brief ������, �⺻������ �����մϴ�.

	\param[in]	defaultLength	�⺻ ����
	\param[in]	defaultSpeed	�⺻ �ӵ�
	*/
	PX_INLINE explicit PxTolerancesScale(float defaultLength=1.0f, float defaultSpeed=10.0f);

	/**
	\brief ��ũ���Ͱ� ��ȿ�� ��� true�� ��ȯ�մϴ�.
	\return ���� ������ ��ȿ�� ��� true�� ��ȯ�մϴ� (�׻� true�� ��ȯ�մϴ�).
	*/
	PX_INLINE bool isValid() const;

};

PX_INLINE PxTolerancesScale::PxTolerancesScale(float defaultLength, float defaultSpeed) :
	length	(defaultLength),
	speed	(defaultSpeed)
	{
	}

PX_INLINE bool PxTolerancesScale::isValid() const
{
	return length>0.0f;
}

#if !PX_DOXYGEN
} // namespace physx
#endif

/** @} */
#endif
