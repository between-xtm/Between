#include "Engine.h"
#include "learnopengl/1_hello_window.h"
#include "learnopengl/2_hello_triangle.h"
#include "learnopengl/3_shader.h"
#include "learnopengl/4_texture.h"
#include "learnopengl/5_transformation.h"
#include "learnopengl/6_coordinatte_system.h"
#include "learnopengl/7_camera.h"
#include "learnopengl/8_color.h"
#include "learnopengl/9_basic_light.h"
#include "learnopengl/10_material.h"
#include "learnopengl/11_light_map.h"
#include "learnopengl/12_light_caster.h"
#include "learnopengl/13_mutiple_light.h"
#include "learnopengl/14_model_load.h"
#include "learnopengl/15_depth_testing.h"
#include "learnopengl/16_stencil_test.h"
#include "learnopengl/17_blending.h"
#include "learnopengl/18_face_culling.h"
#include "learnopengl/19_framebuffers.h"
#include "learnopengl/20_cubemaps.h"
#include "learnopengl/21-advanced-GLSL.h"
#include "learnopengl/22-geometry-shader.h"
#include "learnopengl/23-Instancing.h"
#include "learnopengl/24_anti_aiasing.h"
#include "learnopengl/test.h"

CameraInstance *CameraInstance::Instance = NULL;
SpecialShaders *SpecialShaders::Instance = NULL;

int main()
{
    int no = 1;
    while (no)
    {
        // __CLEAR_TERMINAL;
        std::cout << "1、你好，窗口；\n"
                     "21、三角形实验1（你好、三角形）；\n"
                     "22、三角形实验2（用顶点组索引绘制正方形）；\n"
                     "201、三角形习题1（绘制两个三角形）；\n"
                     "202、三角形习题1（用不同的VAO和VBO，绘制两个三角形）；\n"
                     "31、着色器实验1（简单着色器程序）；\n"
                     "32、着色器实验2（绿色随时间变化）；\n"
                     "301、着色器习题1（三角形颠倒）；\n"
                     "302、着色器习题2（设置Uniform变量将三角形移动距离）；\n"
                     "303、着色器习题3（将顶点位置设置为颜色输出）；\n"
                     "41、纹理实验1（木箱纹理实验）；\n"
                     "42、纹理实验2（木箱纹理混合颜色）；\n"
                     "43、纹理实验3（两种纹理混合）；\n"
                     "401、纹理习题1（只修改片段着色器，使笑脸颠倒）；\n"
                     "402、纹理习题2（尝试修改纹理环绕方式）；\n"
                     "403、纹理习题3（只显示一个像素）；\n"
                     "404、纹理习题4（键盘控制mix参数）；\n"
                     "51、变换实验1（正方形先缩小再旋转）；\n"
                     "52、变换实验2（正方形不断旋转）；\n"
                     "501、变换习题1（正方形先旋转再位移）；\n"
                     "502、变换习题2（两个正方形不停旋转）；\n"
                     "61、坐标系统实验1（初步进入3D世界）；\n"
                     "62、坐标系统实验1（更多3D）；\n"
                     "63、坐标系统实验1（更多3D箱子）；\n"
                     "601、坐标系统习题1（对projection函数各个参数进行实验）；\n"
                     "602、坐标系统习题2（观察矩阵在各个方向上进行位移）；\n"
                     "603、坐标系统习题3（让3对倍数对箱子运动（包括第一个），其他箱子静止）；\n"
                     "71、摄像机实验1（look at矩阵实验）；\n"
                     "72、摄像机实验2（鼠标输入）；\n"
                     "73、摄像机实验3（自由移动）；\n"
                     "74、摄像机实验4（使用摄像机类）；\n"
                     "701、摄像机习题1（创建FPS相机）；\n"
                     "81、颜色实验1；\n"
                     "91、光照实验1；\n"
                     "901、光照习题1（光源移动）；\n"
                     "902、光照习题2（观察坐标系光照）；\n"
                     "903、光照习题3（Gouraud）；\n"
                     "101、材质实验1；\n"
                     "1001、材质习题1（青色塑料）；\n"
                     "111、光照贴图实验1；\n"
                     "112、光照贴图实验2（镜面贴图）；\n"
                     "1101、光照贴图习题1（反转镜面贴图）；\n"
                     "1102、光照贴图习题2（彩色镜面贴图）；\n"
                     "1103、光照贴图习题3（自发光贴图）；\n"
                     "121、投光物实验1（平行光）；\n"
                     "122、投光物实验2（衰减平行光）；\n"
                     "123、投光物实验3（聚光）；\n"
                     "124、投光物实验4（聚光平滑/软化边缘）；\n"
                     "131、多光源实验1；\n"
                     "141、模型加载实验；\n"
                     "151、深度测试实验1；\n"
                     "152、深度测试实验2(深度值精度线性)；\n"
                     "153、深度测试实验2(深度值精度非线性)；\n"
                     "161、模版测试实验1；\n"
                     "171、混合实验1；\n"
                     "172、混合实验2（半透明）；\n"
                     "181、面剔除实验；\n"
                     "191、帧缓冲实验1；\n"
                     "192、帧缓冲实验2（后处理之反相）；\n"
                     "193、帧缓冲实验3（后处理之灰度）；\n"
                     "194、帧缓冲实验4（后处理之核方法）；\n"
                     "2001、立方体贴图实验1；\n"
                     "2002、立方体贴图实验2-优化；\n"
                     "2003、立方体贴图实验3-反射；\n"
                     "2004、立方体贴图实验4-模型加载的反射；\n"
                     "2005、立方体贴图实验5-模型加载的折射；\n"
                     "2101、高级GLSL-PointSize内建变量实验1-gl_PointSize；\n"
                     "2102、高级GLSL-PointSize内建变量实验2；\n"
                     "2103、高级GLSL-PointSize内建变量实验3-gl_FragCoord；\n"
                     "2104、高级GLSL-PointSize内建变量实验4-gl_FrontFacing\n"
                     "2105、高级GLSL-PointSize内建变量实验5-Uniform块布局\n"
                     "2106、高级GLSL-PointSize内建变量实验6-接口块\n"
                     "2201、几何着色器实验1\n"
                     "2202、几何着色器实验1-造房子\n"
                     "2203、几何着色器实验2-爆炸\n"
                     "2204、几何着色器实验3-法线可视化\n"
                     "2301、实例化实验1（未使用实例化）\n"
                     "2302、实例化实验2（使用了实例化）\n"
                     "2303、实例化实验3（实例化数组）\n"
                     "2304、实例化实验4（未使用实例化渲染行星）\n"
                     "2305、实例化实验5（使用实例化渲染行星）\n"
                     "2401、抗锯齿实验1（MSAA）\n"
                     "2401、抗锯齿实验1（帧缓冲MSAA）\n"
                     "-1、绘制物体网格\n";
        std::cout << "请输入编号（输入0退出程序）：";
        std::cin >> no;
        switch (no)
        {
        case 1:
            glx001::main();
            break;
        case 21:
            glx021::main();
            break;
        case 22:
            glx022::main();
            break;
        case 201:
            glxe021::main();
            break;
        case 202:
            glxe022::main();
            break;
        case 31:
            glx031::main();
            break;
        case 32:
            glx032::main();
            break;
        case 301:
            glxe031::main();
            break;
        case 302:
            glxe032::main();
            break;
        case 303:
            glxe033::main();
            break;
        case 41:
            glx041::main();
            break;
        case 42:
            glx042::main();
            break;
        case 43:
            glx043::main();
            break;
        case 401:
            glxe041::main();
            break;
        case 402:
            glxe042::main();
            break;
        case 403:
            glxe043::main();
            break;
        case 404:
            glxe044::main();
            break;
        case 51:
            glx051::main();
            break;
        case 52:
            glx052::main();
            break;
        case 501:
            glxe051::main();
            break;
        case 502:
            glxe052::main();
            break;
        case 61:
            glx061::main();
            break;
        case 62:
            glx062::main();
            break;
        case 63:
            glx063::main();
            break;
        case 601:
            glxe061::main();
            break;
        case 602:
            glxe062::main();
        case 603:
            glxe063::main();
            break;
        case 71:
            glx071::main();
            break;
        case 72:
            glx072::main();
            break;
        case 73:
            glx073::main();
            break;
        case 74:
            glx074::main();
            break;
        case 701:
            glxe071::main();
            break;
        case 81:
            glx081::main();
            break;
        case 91:
            glx091::main();
            break;
        case 901:
            glxe091::main();
            break;
        case 902:
            glxe092::main();
            break;
        case 903:
            glxe093::main();
            break;
        case 101:
            glx0101::main();
            break;
        case 1001:
            glxe0101::main();
            break;
        case 111:
            glx0111::main();
            break;
        case 112:
            glx0112::main();
            break;
        case 1101:
            glxe0111::main();
            break;
        case 1102:
            glxe0112::main();
            break;
        case 1103:
            glxe0113::main();
            break;
        case 121:
            glx0121::main();
            break;
        case 122:
            glx0122::main();
            break;
        case 123:
            glx0123::main();
            break;
        case 124:
            glx0124::main();
            break;
        case 131:
            glx0131::main();
            break;
        case 141:
            glx0141::main();
            break;
        case 151:
            glx0151::main();
            break;
        case 152:
            glx0152::main();
            break;
        case 153:
            glx0153::main();
            break;
        case 161:
            glx0161::main();
            break;
        case 171:
            glx0171::main();
            break;
        case 172:
            glx0172::main();
            break;
        case 181:
            glx0181::main();
            break;
        case 191:
            glx0191::main();
            break;
        case 192:
            glx0192::main();
            break;
        case 193:
            glx0193::main();
            break;
        case 194:
            glx0194::main();
            break;
        case 2001:
            glx0201::main();
            break;
        case 2002:
            glx0202::main();
            break;
        case 2003:
            glx0203::main();
            break;
        case 2004:
            glx0204::main();
            break;
        case 2005:
            glx0205::main();
            break;
        case 2101:
            glx0211::main();
            break;
        case 2102:
            glx0212::main();
            break;
        case 2103:
            glx0213::main();
            break;
        case 2104:
            glx0214::main();
            break;
        case 2105:
            glx0215::main();
            break;
        case 2106:
            glx0216::main();
            break;
        case 2201:
            glx0221::main();
            break;
        case 2202:
            glx0222::main();
            break;
        case 2203:
            glx0223::main();
            break;
        case 2204:
            glx0224::main();
            break;
        case 2301:
            glx0231::main();
            break;
        case 2302:
            glx0232::main();
            break;
        case 2303:
            glx0233::main();
            break;
        case 2304:
            glx0234::main();
            break;
        case 2305:
            glx0235::main();
            break;
        case 2401:
            glx0241::main();
            break;
        case 2402:
            glx0242::main();
            break;
        case -1:
            test1::main();
            break;
        case -2:
            test1::main();
            break;
        default:
            break;
        }
    }

    __CLEAR_TERMINAL;
}