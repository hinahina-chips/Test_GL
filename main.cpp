/*
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>

// GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// made class
#include "object.h"
#include "shader.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif

void checkGLError()
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}
}

using namespace std;
using namespace cv;

int main() 
{
	static const GLfloat g_vertex_buffer_data[] = {
	0.5f, 0.5f, 0.0f, //四角形一つ目
			 0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f,  0.0f,
			-0.5f, -0.5f, 0.0f,
	};
	// variables---------------
	GLuint ProgramID;
	GLuint vao;
	GLuint vbo;
	//-------------------------

	if (glfwInit() == GL_FALSE) 
	{
		cerr << "Can't initialize GLFW." << endl;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *const window(glfwCreateWindow(1020, 760, "Hello!", NULL, NULL));
	if (window == NULL)
	{
		cerr << "Can't create GLFW window" << endl;
		return 1;
	}

	atexit(glfwTerminate);

	glfwMakeContextCurrent(window);

	// GLEWの初期化
	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		cerr << "Can't initialize FLEW" << endl;
		return 1;
	}

	glfwSwapInterval(1);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// LoadShaders
	ProgramID = LoadShaders("Simple.vert", "Simple.frag");
	cout << ProgramID << endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
    

	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0);

		// 描画処理-----------------------------------------
		glUseProgram(ProgramID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableVertexAttribArray(0);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	return 0;
}

/*
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>

// GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// made class
#include "object.h"
#include "shader.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif

using namespace std;

const int g_width = 640;
const int g_height = 480;

int main()
{

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "Simple", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// モニタとの同期
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLuint programId = LoadShaders("Simple.vert", "Simple.frag");

	// ゲームループ
	while (!glfwWindowShouldClose(window)) {

		// 画面の初期化
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0);

		// 頂点データ
		float vertex_position[] = {
			1.0f, 1.0f,
			-1.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, -1.0f
		};

		// 何番目のattribute変数か
		int attLocation = glGetAttribLocation(programId, "position");

		// attribute属性を有効にする
		glEnableVertexAttribArray(attLocation);

		// attribute属性を登録
		glVertexAttribPointer(attLocation, 2, GL_FLOAT, false, 0, vertex_position);

		// モデルの描画
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		// バッファの入れ替え
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
*/

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>

// GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// made class
#include "object.h"
#include "shader.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif

int main() {
	GLFWwindow* window = NULL;
	const GLubyte* renderer;
	const GLubyte* version;

	GLfloat points[] = { 0.5f, 0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				-0.5f, 0.5f,  0.0f,
				-0.5f, -0.5f, 0.0f };

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(1000, 800, "Rectangle", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	GLint shader = LoadShaders("Simple.vert", "Simple.frag");
	GLuint vao;
	GLuint vertex_vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 頂点座標のVBOを作成	
	glGenBuffers(1, &vertex_vbo); //バッファを作成
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); //実データを格納

	// texture mapping-------------------
	GLuint tex;
	//テクスチャオブジェクトの生成
	glGenTextures(1, &tex);

	//テクスチャのバインド
	glBindTexture(GL_TEXTURE_2D, tex);

	// テクスチャ読み込み
	cv::Mat img = cv::imread("input2.jpg");

	//テクスチャにデータを紐付ける
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	/*
	//テクスチャのフィルタリング設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//テクスチャのリピート設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	*/
	//テクスチャユニットを指定
	glViewport(0, 0, 1000, 800);
	glActiveTexture(GL_TEXTURE0);

	//テクスチャをバインド
	glBindTexture(GL_TEXTURE_2D, tex);

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(shader, "myTextureSampler");
	glUniform1i(TextureID, 0);

	//--------------------------
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableVertexAttribArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}