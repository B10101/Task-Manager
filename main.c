#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>

#define WIN_MARGIN 20.0f
static int winw = 1200, winh = 720;
static LfFont titlefont;

static void renderTopBar(){

  lf_push_font(&titlefont);
    lf_text("Your Todo");
  lf_pop_font();

  {
    const float width = 160.0f;
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 2.0f);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    props.color = (LfColor){56,233,246,255};
    props.border_width = 0.0f;
    props.corner_radius = 4.0f;

    lf_push_style_props(props);
    lf_set_line_should_overflow(false);
    lf_button_fixed("New Task" , width, -1);
    lf_set_line_should_overflow(true);
    lf_pop_style_props();
  }

}

int main()
{
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(winw,winh, "Todo" , NULL, NULL);
  glfwMakeContextCurrent(window);

  lf_init_glfw(winw,winh, window);

  LfTheme theme = lf_get_theme();
  theme.div_props.color = LF_NO_COLOR;
  lf_set_theme(theme);
  titlefont = lf_load_font("./Roboto_Mono/static/RobotoMono-Bold.ttf",40);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.01f, 0.01f, 0.01f,1.0f);

  lf_begin();

  lf_div_begin(((vec2s){WIN_MARGIN , WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), true);
  
  renderTopBar();

  lf_next_line();
  
  
   {
      const uint32_t numfilters = 5;
      static const char* filters[] = 
      {"ALL", "IN PROGRESS", "COMPLETED", "LOW", "HIGH"};
      for(uint32_t i = 0; i < numfilters; i++){
        LfUIElementProps props = lf_get_theme().text_props;
        lf_push_style_props(props);
        lf_button(filters[i]);
        lf_pop_style_props();
      }
   }
  lf_div_end();

  lf_end();

    glfwPollEvents();
    glfwSwapBuffers(window);

  }
  lf_free_font(&titlefont);
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
