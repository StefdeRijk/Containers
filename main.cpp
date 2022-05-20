#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include <vector>

template <typename T> void print_proper_vec(std::vector<T> vec, size_t size, std::ofstream& file)
{
	for (size_t i = 0; i < size; i++) {
		file << vec[i] << std::endl;
	}
}

template <typename T> void print_vec(ft::vector<T> vec, size_t size, std::ofstream& file)
{
	for (size_t i = 0; i < size; i++) {
		file << vec[i] << std::endl;
	}
}

int main(void)
{
	std::ofstream	proper_output;
	proper_output.open("proper_output");
	int i = 10;
	std::string str = "Hello world!";
	std::vector<int>	proper_vec_empty;
	print_proper_vec(proper_vec_empty, proper_vec_empty.size(), proper_output);
	std::vector<int>	proper_vec_5_int(5, i);
	print_proper_vec(proper_vec_5_int, proper_vec_5_int.size(), proper_output);
	std::vector<std::string>	proper_vec_3_str(3, str);
	print_proper_vec(proper_vec_3_str, proper_vec_3_str.size(), proper_output);
	std::vector<int>	proper_vec_5_int_iterator(proper_vec_5_int.begin(), proper_vec_5_int.end());
	print_proper_vec(proper_vec_5_int_iterator, proper_vec_5_int.size(), proper_output);
	std::vector<std::string>	proper_vec_3_str_copy(proper_vec_3_str);
	print_proper_vec(proper_vec_3_str_copy, proper_vec_3_str_copy.size(), proper_output);
	proper_vec_empty = proper_vec_5_int;
	print_proper_vec(proper_vec_empty, proper_vec_empty.size(), proper_output);
	proper_vec_3_str_copy[0] = "Hello world first";
	proper_vec_3_str_copy[1] = "Hello world second";
	proper_vec_3_str_copy[2] = "Hello world third";
	std::vector<std::string>::reverse_iterator	proper_rev_it = proper_vec_3_str_copy.rbegin(); 
	proper_output << *proper_rev_it << std::endl;
	proper_rev_it = proper_vec_3_str_copy.rend();
	proper_rev_it--;
	proper_output << *proper_rev_it << std::endl;

	proper_output.close();

	std::cout << std::endl;

	std::ofstream	my_output;
	my_output.open("my_output");
	ft::vector<int>	vec_empty;
	print_vec(vec_empty, vec_empty.size(), my_output);
	ft::vector<int>	vec_5_int(5, i);
	print_vec(vec_5_int, vec_5_int.size(), my_output);
	ft::vector<std::string>	vec_3_str(3, str);
	print_vec(vec_3_str, vec_3_str.size(), my_output);
	ft::vector<int>	vec_5_int_iterator(vec_5_int.begin(), vec_5_int.end());
	print_vec(vec_5_int_iterator, vec_5_int.size(), my_output);
	ft::vector<std::string>	vec_3_str_copy(vec_3_str);
	print_vec(vec_3_str_copy, vec_3_str_copy.size(), my_output);
	vec_empty = vec_5_int;
	print_vec(vec_empty, vec_empty.size(), my_output);
	vec_3_str_copy[0] = "Hello world first";
	vec_3_str_copy[1] = "Hello world second";
	vec_3_str_copy[2] = "Hello world third";
	ft::vector<std::string>::reverse_iterator	rev_it = vec_3_str_copy.rbegin(); 
	my_output << *rev_it << std::endl;
	rev_it = vec_3_str_copy.rend();
	rev_it--;
	my_output << *rev_it << std::endl;

	my_output.close();

	system("leaks Containers");
	system("diff proper_output my_output");
	return (0);
}
