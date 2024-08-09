#include "pch.h"
#include "CppUnitTest.h"
#include "ObjectPool.h"
#include "AABB.h"
#include "Vector3.cpp"
#include "AABB.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(objectPoolBackToFront)
		{
			ObjectPool<int> numbers(5);
			numbers[0] = 1;
			numbers[1] = 2;
			numbers[2] = 3;
			numbers[3] = 4;
			numbers[4] = 5;
			numbers.BeginOfArray();
			Assert::AreEqual(5, numbers[0]);
		}

		TEST_METHOD(objectPoolToBack)
		{
			ObjectPool<int> numbers(5);
			numbers[0] = 1;
			numbers[1] = 2;
			numbers[2] = 3;
			numbers[3] = 4;
			numbers[4] = 5;
			numbers.EndOfArray(numbers[3]);
			Assert::AreEqual(4, numbers[3]);
		}

		TEST_METHOD(spatialPartitioningOne)
		{
			AABB boxOne(MathClasses::Vector3{ 0, 0, 1 }, MathClasses::Vector3{ 2, 2, 1 });
			MathClasses::Vector3 pointOne = {3, 3, 1};

			Assert::IsFalse(boxOne.Overlaps(pointOne));
		}

		TEST_METHOD(spatialPartitioningTwo)
		{
			AABB boxOne(MathClasses::Vector3{ 0, 0, 1 }, MathClasses::Vector3{ 2, 2, 1 });
			MathClasses::Vector3 pointOne = { 1, 3, 1 };

			Assert::IsFalse(boxOne.Overlaps(pointOne));
		}

		TEST_METHOD(spatialPartitioningThree)
		{
			AABB boxOne(MathClasses::Vector3{ 0, 0, 1 }, MathClasses::Vector3{ 2, 2, 1 });
			MathClasses::Vector3 pointOne = { 3, 1, 1 };

			Assert::IsFalse(boxOne.Overlaps(pointOne));
		}

		TEST_METHOD(spatialPartitioningFour)
		{
			AABB boxOne(MathClasses::Vector3{ 0, 0, 1 }, MathClasses::Vector3{ 2, 2, 1 });
			MathClasses::Vector3 pointOne = { 1, 1, 1 };

			Assert::IsTrue(boxOne.Overlaps(pointOne));
		}
	};
}
