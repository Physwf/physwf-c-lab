#ifndef _INPUT_H_
#define _INPUT_H_

namespace Toy3D {

	class Input
	{
	public:
		Input();
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		Input(Input&&) = delete;
		Input& operator=(Input&&) = delete;
		~Input();

		void Initialize();
		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);
	private:
		bool m_keys[256];
	};
}
#endif