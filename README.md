# 复 刻 经 典
完  全  一  致

![Image text](https://github.com/137900114/tony-render-pipeline/blob/master/RP/RenderPics/sphere.png)

![Image text](https://github.com/137900114/tony-render-pipeline/blob/master/RP/RenderPics/1573439125310.jpeg)

渲染详细代码请看 源.cpp的内容

主要模拟了一个小型的渲染管线

主要阶段：

Drawable的数据 -》 顶点着色器（Shader.vertex） -》  光栅化 -》 深度缓冲 -》 片源着色器(Shader.fragment) -》 输出

因为深度缓冲在片源着色阶段之前因此渲染不了透明物体

没有中间插值阶段，插值必须得在片源着色器阶段进行。。。

vertex 和 fragment是可编程的。现在给出了两个不同的编程实现(UtilShader 和 BinlingPhong)

渲染管线接受一个Drawable对象。Drawable对象包含几何体所有的面和点的数据。

输出结构为一个Image对象，Image可以设置每个像素点的颜色值，本次渲染后的数据保存在png格式里。只要继承了Image接口，渲染结果是可以输出为任何形式的

球体的构造是在Sphere.h和Sphere.cpp中完成的。大概就是通过构造一个多面体实现的。构造的时候可以通过填sample 选项改变球体面数。渲染时采用了Binling Phong反射模型。具体实现可以在BinlingPhong.h 和BinlingPhong.cpp中查看

墙面在Plane.h中实现。采用了UtilShader实现具体见于文件中

现在加上了多重采样，可以抗边缘锯齿化
![Image text](https://github.com/137900114/tony-render-pipeline/blob/master/mass.png)
具体可以看ImageMASS.h 和 ImageMass.cpp
