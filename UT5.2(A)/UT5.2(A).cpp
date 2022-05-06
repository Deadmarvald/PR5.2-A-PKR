#include "pch.h"
#include "CppUnitTest.h"
#include "../PKR5.2(A)/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT52A
{
	TEST_CLASS(UT52A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			fstream fout("filetest1", ios::binary);

			Student s;
			for (int i = 0; i < 2; i++)
			{
				s.secondname;
				s.kurs = 1;
				s.physics = 5;
				s.math = 5;
				s.inf = 5;

				fout.write((char*)&s, sizeof(Student));
			}

			double t = LineSearch("filetest1");

			Assert::AreEqual(t, 100.0);
		}
	};
}