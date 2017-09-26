#ifndef SHADER
#define SHADER

class Shader
{
public:
	GLuint vertexShader, fragmentShader, shaderProgram;
	Shader(const char* vertPath, const char* fragPath);
	GLint getUniformLoc(const char* name);
	void setProjection(glm::mat4);
	void setView(glm::mat4);
	void setModel(glm::mat4);
	void enable();
	void disable();
private:
	int projLoc, viewLoc, modelLoc;
};

class Shader2c : public Shader
{
	public:
		Shader2c();
		~Shader2c();
		void setColor(float r, float g, float b, float a);
	private:
		int colorLoc;
		void getUniformLocs();
};

class Shader2t : public Shader
{
	public:
		Shader2t();
		~Shader2t();
};

#endif
