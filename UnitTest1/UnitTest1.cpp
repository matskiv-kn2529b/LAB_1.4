#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Mackiv\source\repos\LAB_1.4\LAB_1.4\Stack.h"
#include "C:\Users\Mackiv\source\repos\LAB_1.4\LAB_1.4\TrainSorter.h"
#include "C:\Users\Mackiv\source\repos\LAB_1.4\LAB_1.4\Stack.cpp"
#include "C:\Users\Mackiv\source\repos\LAB_1.4\LAB_1.4\TrainSorter.cpp"

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLAB14
{
	TEST_CLASS(StackTests)
	{
	public:

		// Тест 1: Ініціалізація та початковий стан
		TEST_METHOD(TestInitialization)
		{
			Stack s(10);
			Assert::AreEqual(0, s.getCount());
			Assert::AreEqual(10, s.getCapacity());
			Assert::IsTrue(s.isEmpty());
		}

		// Тест 2: Конструктор за замовчуванням та Init
		TEST_METHOD(TestDefaultConstructorAndInit)
		{
			Stack s;
			Assert::AreEqual(0, s.getCount());
			Assert::IsTrue(s.getCapacity() > 0);

			s.push(1);
			s.Init(7);
			Assert::AreEqual(0, s.getCount());
			Assert::AreEqual(7, s.getCapacity());

			// Некоректна ємність -> значення за замовчуванням (10)
			s.Init(-3);
			Assert::AreEqual(10, s.getCapacity());
			Assert::AreEqual(0, s.getCount());
		}

		// Тест 3: Операції Push та Pop
		TEST_METHOD(TestPushAndPop)
		{
			Stack s(5);

			Assert::IsTrue(s.push(10));
			Assert::IsTrue(s.push(20));
			Assert::AreEqual(2, s.getCount());

			int poppedValue = 0;
			Assert::IsTrue(s.pop(poppedValue));
			Assert::AreEqual(20, poppedValue);
			Assert::AreEqual(1, s.getCount());

			Assert::IsTrue(s.peek(poppedValue));
			Assert::AreEqual(10, poppedValue);
			Assert::AreEqual(1, s.getCount()); // peek не видаляє елемент
		}

		// Тест 4: Порядок LIFO та версії pop()/peek() без параметрів
		TEST_METHOD(TestLIFOOrder)
		{
			Stack s(3);
			s.push(1);
			s.push(2);
			s.push(3);

			Assert::AreEqual(3, s.peek());
			Assert::AreEqual(3, s.pop());
			Assert::AreEqual(2, s.pop());
			Assert::AreEqual(1, s.pop());
			Assert::IsTrue(s.isEmpty());
		}

		// Тест 5: Стек НЕ обмежений -- автоматичне зростання понад початкову ємність
		TEST_METHOD(TestStackGrowsAutomatically)
		{
			Stack s(2);
			Assert::IsTrue(s.push(100));
			Assert::IsTrue(s.push(200));

			// Третій push раніше був би переповненням -- тепер успішний
			Assert::IsTrue(s.push(300));
			Assert::AreEqual(3, s.getCount());
			Assert::IsTrue(s.getCapacity() >= 3);
			Assert::AreEqual(300, s.peek());

			// Значно більше за старі 100 елементів
			for (int i = 0; i < 1000; ++i) {
				Assert::IsTrue(s.push(i));
			}
			Assert::AreEqual(1003, s.getCount());
			Assert::AreEqual(999, s.peek());

			// Усі елементи збереглися після перевиділень пам'яті
			Assert::AreEqual(100, s.getElement(0));
			Assert::AreEqual(200, s.getElement(1));
			Assert::AreEqual(300, s.getElement(2));
		}

		// Тест 6: Спроба Pop та Peek з порожнього стека
		TEST_METHOD(TestPopAndPeekUnderflow)
		{
			Stack s(5);
			int val = 0;
			Assert::IsFalse(s.pop(val));
			Assert::IsFalse(s.peek(val));
			Assert::AreEqual(0, s.getCount());
		}

		// Тест 7: Перевірка валідації у сеттерах
		TEST_METHOD(TestSettersValidation)
		{
			Stack s(10);

			// Некоректне значення ємності
			Assert::IsFalse(s.setCapacity(-5));
			Assert::IsFalse(s.setCapacity(0));
			Assert::AreEqual(10, s.getCapacity());

			// Коректне значення (верхньої межі більше немає)
			Assert::IsTrue(s.setCapacity(20));
			Assert::AreEqual(20, s.getCapacity());
			Assert::IsTrue(s.setCapacity(500));
			Assert::AreEqual(500, s.getCapacity());

			// Ємність не може бути меншою за кількість елементів (щоб не втратити дані)
			s.push(1);
			s.push(2);
			s.push(3);
			Assert::IsFalse(s.setCapacity(2));
			Assert::AreEqual(500, s.getCapacity());
			Assert::AreEqual(3, s.getCount());
			Assert::IsTrue(s.setCapacity(3)); // рівно за кількістю -- можна
			Assert::AreEqual(3, s.getElement(2));

			// Некоректне значення кількості елементів
			Assert::IsFalse(s.setCount(-1));
			Assert::IsFalse(s.setCount(s.getCapacity() + 1));
			Assert::AreEqual(3, s.getCount());

			// Коректне значення кількості
			Assert::IsTrue(s.setCount(2));
			Assert::AreEqual(2, s.getCount());
		}

		// Тест 8: getElement / setElement
		TEST_METHOD(TestGetSetElement)
		{
			Stack s(5);
			s.push(10);
			s.push(20);

			Assert::AreEqual(10, s.getElement(0));
			Assert::AreEqual(20, s.getElement(1));
			Assert::AreEqual(-1, s.getElement(2));   // поза межами
			Assert::AreEqual(-1, s.getElement(-1));

			Assert::IsTrue(s.setElement(0, 99));
			Assert::AreEqual(99, s.getElement(0));
			Assert::IsFalse(s.setElement(2, 5));     // немає такого елемента
			Assert::IsFalse(s.setElement(-1, 5));
		}

		// Тест 9: clear
		TEST_METHOD(TestClear)
		{
			Stack s(5);
			s.push(1);
			s.push(2);
			s.clear();
			Assert::AreEqual(0, s.getCount());
			Assert::IsTrue(s.isEmpty());
			Assert::IsTrue(s.push(7)); // після очищення стек працює
			Assert::AreEqual(7, s.peek());
		}

		// Тест 10: Конструктор копіювання -- копія незалежна від оригіналу
		TEST_METHOD(TestCopyConstructor)
		{
			Stack a(3);
			a.push(1);
			a.push(2);

			Stack b(a);
			b.push(3);
			b.setElement(0, 100);

			Assert::AreEqual(2, a.getCount());
			Assert::AreEqual(1, a.getElement(0));
			Assert::AreEqual(3, b.getCount());
			Assert::AreEqual(100, b.getElement(0));
		}

		// Тест 11: Оператор присвоєння, у тому числі самоприсвоєння
		TEST_METHOD(TestAssignmentOperator)
		{
			Stack a(3);
			a.push(5);
			a.push(6);

			Stack b(10);
			b.push(1);
			b = a;
			Assert::AreEqual(2, b.getCount());
			Assert::AreEqual(6, b.peek());

			b.push(7);
			Assert::AreEqual(2, a.getCount()); // a не змінився

			Stack& ref = a;
			a = ref; // самоприсвоєння не ламає об'єкт
			Assert::AreEqual(2, a.getCount());
			Assert::AreEqual(5, a.getElement(0));
		}

		// Тест 12: toString містить усі елементи
		TEST_METHOD(TestToString)
		{
			Stack s(5);
			s.push(11);
			s.push(22);
			std::string str = s.toString();
			Assert::IsTrue(str.find("11") != std::string::npos);
			Assert::IsTrue(str.find("22") != std::string::npos);
		}
	};

	TEST_CLASS(TrainSorterTests)
	{
	public:

		// Тест 13: Перевірка алгоритму сортування Т-подібного вузла
		TEST_METHOD(TestTrainSortingAlgorithm)
		{
			std::vector<int> inputTrain = { 1, 2, 1, 2, 2, 1 };
			std::vector<int> track1, track2;
			Stack sortingStack(100);

			TrainSorter::sortTrain(inputTrain, track1, track2, sortingStack);

			// На Колію 1 повинні потрапити три вагони типу 1
			Assert::AreEqual((size_t)3, track1.size());
			for (int val : track1) {
				Assert::AreEqual(1, val);
			}

			// На Колію 2 повинні потрапити три вагони типу 2
			Assert::AreEqual((size_t)3, track2.size());
			for (int val : track2) {
				Assert::AreEqual(2, val);
			}

			// Тупик після сортування порожній
			Assert::IsTrue(sortingStack.isEmpty());
		}

		// Тест 14: Потяг, довший за 100 вагонів, і малий початковий стек
		TEST_METHOD(TestLongTrainWithSmallStack)
		{
			std::vector<int> inputTrain(500, 2);
			inputTrain.push_back(1);
			std::vector<int> track1, track2;
			Stack sortingStack(2);

			TrainSorter::sortTrain(inputTrain, track1, track2, sortingStack);

			Assert::AreEqual((size_t)1, track1.size());
			Assert::AreEqual((size_t)500, track2.size());
		}

		// Тест 15: Порожній потяг та потяг з одного типу
		TEST_METHOD(TestEmptyAndSingleTypeTrain)
		{
			std::vector<int> track1, track2;
			Stack sortingStack;

			TrainSorter::sortTrain(std::vector<int>(), track1, track2, sortingStack);
			Assert::IsTrue(track1.empty());
			Assert::IsTrue(track2.empty());

			TrainSorter::sortTrain(std::vector<int>{ 1, 1, 1 }, track1, track2, sortingStack);
			Assert::AreEqual((size_t)3, track1.size());
			Assert::IsTrue(track2.empty());
		}

		// Тест 16: Читання потягу з файлу
		TEST_METHOD(TestReadTrainFromFile)
		{
			std::string fileName = "unit_test_train.txt";
			Assert::IsTrue(TrainSorter::createSampleFile(fileName));

			std::vector<int> train = TrainSorter::readTrainFromFile(fileName);
			Assert::AreEqual((size_t)10, train.size());
			Assert::AreEqual(1, train[0]);
			Assert::AreEqual(2, train[1]);

			// Неіснуючий файл -> порожній потяг
			std::vector<int> none = TrainSorter::readTrainFromFile("no_such_file_123.txt");
			Assert::IsTrue(none.empty());
		}
	};
}
