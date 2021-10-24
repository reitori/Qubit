namespace Qubit {

	__declspec(dllimport) void test(const char* message);

}

int main() {

	Qubit::test("Hello World");
}