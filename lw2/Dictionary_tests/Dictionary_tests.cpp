#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Dictionary/Dictionary.h"

const std::string TEST_DICTIONARY_PATH = "test_dictionary.txt";
const std::string TEST_INVALID_DICTIONARY_PATH = "invalid_test_dictionary.txt";
const std::string TEST_EMPTY_DICTIONARY_PATH = "empty_test_dictionary.txt";

TEST_CASE("Open test dictionary")
{
	auto dictionary = GetDictionary(TEST_DICTIONARY_PATH);

	std::map<std::string, std::string> expectedDictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	CHECK(dictionary == expectedDictionary);
}

TEST_CASE("Open empty dictionary")
{
	auto dictionary = GetDictionary(TEST_EMPTY_DICTIONARY_PATH);

	std::map<std::string, std::string> expectedDictionary = {};

	CHECK(dictionary == expectedDictionary);
}

TEST_CASE("Open invalid dictionary")
{
	CHECK_THROWS_WITH(GetDictionary(TEST_INVALID_DICTIONARY_PATH), "����������� ����� �������. ���������� ������ ����.");
}

TEST_CASE("Translate word in the dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	std::string word = "cat";
	auto result = Translate(word, dictionary);
	CHECK(result == "�����");
}

TEST_CASE("Translate word which is not in the dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	std::string word = "cats";
	auto result = Translate(word, dictionary);
	CHECK(result == "");
}

TEST_CASE("Translate uppercase word in the dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	std::string word = "CAT";
	auto result = Translate(word, dictionary);
	CHECK(result == "�����");
}

TEST_CASE("Add new word to the dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	dictionary["tortoise"] = "��������";

	std::map<std::string, std::string> expectedDictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"},
		{"tortoise", "��������"}
	};

	CHECK(dictionary == expectedDictionary);
}

TEST_CASE("Add existed word to the dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	dictionary["cat"] = "���";

	std::map<std::string, std::string> expectedDictionary = {
		{"cat", "���"},
		{"dog", "������"},
		{"home", "���"}
	};

	CHECK(dictionary == expectedDictionary);
}

// �������� ����� �������
// ����������� ������� �� ����� ������
TEST_CASE("Save dictionary to file and assert with saved dictionary")
{
	std::map<std::string, std::string> dictionary = {
		{"cat", "�����"},
		{"dog", "������"},
		{"home", "���"}
	};

	SaveDictionary(TEST_DICTIONARY_PATH, dictionary);

	auto savedDictionary = GetDictionary(TEST_DICTIONARY_PATH);
	
	CHECK(dictionary == savedDictionary);
}