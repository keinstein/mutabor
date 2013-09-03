/** \file               -*- C++ -*-
 ********************************************************************
 * Test BoxClass.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
#ifndef __BOXTEST_H__
#define __BOXTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Box.h"
#include "src/kernel/Runtime.h"

class BoxTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( BoxTest );
	CPPUNIT_TEST( testGetNextFreeBox );
	CPPUNIT_TEST( testParser );
	CPPUNIT_TEST( testCopyPLay );
	CPPUNIT_TEST_SUITE_END();

protected:
//	mutabor::Box Box;

public:
	BoxTest()
	{
	}

	virtual ~BoxTest()
	{
	}

	int countTestCases () const
	{ 
		return 3; 
	}
  
	void setUp();
	void tearDown();

	void testGetNextFreeBox() 
	{ 	  
		mutabor::Box Box0 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
		CPPUNIT_ASSERT( Box0->get_routefile_id() == 0 );
		mutabor::Box Box1 = mutabor::BoxFactory::Create(mutabor::Box0);
		CPPUNIT_ASSERT( Box1->get_routefile_id() == 1 );
		mutabor::Box Box2 = mutabor::BoxFactory::Create(mutabor::Box0,5);
		CPPUNIT_ASSERT( Box2->get_routefile_id() == 5 );
		mutabor::Box Box3 = mutabor::BoxFactory::Create(mutabor::Box0);
		CPPUNIT_ASSERT( Box3->get_routefile_id() == 6 );
		Box1->Destroy();
		Box1=NULL;
		Box2->Destroy();
		Box2=NULL;
		Box1 = mutabor::BoxFactory::Create(mutabor::Box0,4);
		CPPUNIT_ASSERT( Box1->get_routefile_id() == 4 );
		Box2 = mutabor::BoxFactory::Create(mutabor::Box0);
		CPPUNIT_ASSERT( Box2->get_routefile_id() == 7 );
		mutabor::Box Box4 = mutabor::BoxFactory::Create(mutabor::Box0,5);
		CPPUNIT_ASSERT( Box4->get_routefile_id() == 5 );
		CPPUNIT_ASSERT( mutabor::BoxClass::GetNextFreeBox() == 8);
		Box0->Destroy();
		Box1->Destroy();
		Box2->Destroy();
		Box3->Destroy();
		Box4->Destroy();
	}

	void testParser();
	void testCopyPLay();

};

#endif
/// \}
