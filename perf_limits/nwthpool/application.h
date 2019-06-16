#ifndef APPLICATION_H
#define APPLICATION_H

class Application{
	static Application* ms_instance;

private:
	Application(const Application& rhs);
	Application& operator=(const Application& rhs);

public:
	static Application* Instance();
	static void Release();

	void run();
	
private:
	Application();
	~Application();

};

#endif // APPLICATION_H
