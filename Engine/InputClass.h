////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
enum class KeyCode {
	W, A, S, D,
	ESCAPE, LSHFIT,
	F1, F2,ONE,TWO,THREE ,SPACE,Q,E,T
};



class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool GetKey(KeyCode key);
	bool GetKeyDown(KeyCode key);
	bool GetKeyUp(KeyCode key);

	void GetMouseLocation(int&, int&);
	void GetMouseDeltaPosition(int&, int&);
	bool GetLBMouseDown();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();


private:
	IDirectInput8					   *m_directInput;
	IDirectInputDevice8				   *m_keyboard;
	IDirectInputDevice8				   *m_mouse;
	DIMOUSESTATE						m_mouseState;
	map<KeyCode, unsigned char>			m_keyState;
	unsigned char						m_keyboardState[256];
	unsigned char						m_pressedKeys[256];
	int									m_screenWidth, m_screenHeight;
	int									m_mouseX, m_mouseY;
};

#endif