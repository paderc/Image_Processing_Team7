#include <string>

#include "Modifier.h"

class Geometric_Mean_Modifier : public Modifier {
public:
	Geometric_Mean_Modifier(char* argv[]) : 
		Modifier(argv),
		width(image.width()),
		height(image.height()),
		m(stoi(argv[3])),
		n(stoi(argv[4]))
	{
		m = clamp(m, 0, 13);
		n = clamp(n, 0, 13);
	}
private:
	int width;
	int height;
	int m;
	int n;
	void modify_inherited() override;
	string make_name(string_view base_name, string_view extension) override;
};