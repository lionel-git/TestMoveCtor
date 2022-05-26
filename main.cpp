#include <iostream>
#include <map>
#include <vector>

struct MyData
{
	MyData(){ std::cout << "Ctor" << std::endl; }
	/*MyData(const std::string& s, int a)
	{
		values[s] = 17;
		age = a;
	}*/
	MyData(const MyData& rhs)
	{
		*this = rhs;
	}

	MyData(MyData&& rhs) noexcept
	{
		*this = std::move(rhs);
	}

	MyData& operator=(MyData&& rhs) noexcept
	{
		std::cout << "Move" << std::endl;
		values = std::move(rhs.values);
		age = std::move(rhs.age);
		return *this;
	}

	MyData& operator=(const MyData& rhs) noexcept
	{
		std::cout << "Copy" << std::endl;
		values = rhs.values;
		age = rhs.age;
		return *this;
	}

	std::map<std::string, int> values;
	int age{0};
};

void fill_vector(std::vector<MyData>& v)
{
	for (int i = 0; i < 13; i++)
	{
		MyData d;
		d.age = i;
		d.values["toto"] = 17;
		v.push_back(std::move(d));
		//v.emplace_back(d);
	}
}

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	
	std::vector<MyData> v;
	//v.reserve(25);
	fill_vector(v);
	std::cout << "=====================" << std::endl;
	//v.reserve(10);
	//MyData d;
	//d.values["toto"] = 5;
	//d.age = 17;
	//v.emplace_back(d);

	MyData d2;
	d2.values["titi"] = 51;
	d2.age = 171;
	v[0] = std::move(d2);

	std::cout << "v=" << v.size() << std::endl;
	std::vector<MyData> v2 = std::move(v);
	std::cout << "v=" << v.size() << std::endl;
	std::cout << "v2=" << v2.size() << std::endl;

	//std::vector<MyData> v3 = v2;
}