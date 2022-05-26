#include <iostream>
#include <map>
#include <vector>

struct SubData
{
	SubData() = default;
	SubData(const SubData& rhs) = default;
	
	// If not defined, Copy ctor is called instead
	SubData(SubData&& rhs) = default;

	std::vector<int> v;
};

struct MyData0
{
	std::map<std::string, int> values;
	SubData sd;
};

struct MyData
{
	MyData() = default;// { std::cout << "Ctor" << std::endl; }
	/*MyData(const std::string& s, int a)
	{
		values[s] = 17;
		age = a;
	}*/
	MyData(const MyData& rhs) = default;
	//MyData& operator=(const MyData& rhs) = default;

	//{
	//	*this = rhs;
	//}

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

	//{
	//	std::cout << "Copy" << std::endl;
	//	values = rhs.values;
	//	age = rhs.age;
	//	return *this;
	//}

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

void testData0()
{
	MyData0 d0;
	d0.values["toto"] = 17;
	MyData0 d1 = d0;
	std::cout << "s1=" << d0.values.size() << std::endl;
	MyData0 d3 = std::move(d0);
	std::cout << "s1=" << d0.values.size() << std::endl;

	std::vector<MyData0> v;
	MyData0 d;
	d.values["titi"] = 17;
	v.push_back(d);
	d.values["toto"] = 22;
	v.push_back(d);

	std::vector<MyData0> v1 = v;
	std::vector<MyData0> v2 = std::move(v);

	v2[0].sd.v.push_back(1121);
	std::vector<MyData0> v3;
	v3.push_back(std::move(v2[0]));
	std::cout << "Subsize: " << v2[0].sd.v.size() << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	
	testData0(); return 1;

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

	std::vector<MyData> v3 = v2;

	


}