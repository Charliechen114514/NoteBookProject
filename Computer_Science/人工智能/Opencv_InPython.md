# opencv(1)---python

##### 图片

​    在计算机眼中，图像由矩阵构成

​    数值的大小表明了图像的亮度，而通道表明了一个颜色：

一个R通道上的255表明这是在Red上很亮

​    下面，我们来介绍一下我们应该怎么读取图像：

```python
import cv2#不同于RGB，我们读取的格式是BGR
import matplotlib.pyplot as plt
import numpy as np
#caution:the input should be the addr of the img
img=cv2.imread("\\imgpath!")

```

读取的结果是：一个nd array

好抽象：可不可以直接展示图片啊：

```python
cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

我们试一下这个：

```python
import cv2
import showimg as simg
import numpy as np
import matplotlib.pyplot as plt
img = cv2.imread('1.png')
simg.imgshow("1",img)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

也可以封装一个函数：

```python
def cv_show(nameWindow,img)
{
     cv2.imshow(nameWindow,img)
	cv2.waitKey(0)
	cv2.destroyAllWindows()
}
```

我们也可以查看一个图片的大小：

```python
img.shape
#(175, 286, 3)
```

我们可以设置读入的方式：比如说读入灰度图

```python
img=cv2.imread("\\imgpath!"，cv2.IMREAD_GREYSCALE)
```

保存我们产出的图像

```python
cv2.imwrite('savedfilename',img)
```

 可以计算像素点的个数：

```python
img.size()
```

###### 视频

​    视频由图像组成，也就是说，我们可以读取视频：

```python
vc=cv2.VideoCapture('videofilepath')
```

​    我们是不是读取成功了？这个看如下的代码判断：

```python
if vc.isOpened():
    open.frame=vc.read()
else:
	open=False

```

​    我们来运行的读取视频

```python
while open:
	ret,frame=vc.read()
    if frame is None:
        break
    if ret==True:
        gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        cv2.imshow('result',gray)
        if cv2.waitKey(10)&0xFF==27:#按下ESC退出或者视频播放完毕
            break
vc.release()
cv2.destroyAllWindows()
```

###### 截取部分图片（ROI）

```python
img=cv2.imgread('Path')
cat=img[0:200,0:200]
cv_show('cat',cat)
```

这样我们就利用切片截取了部分图片了.

###### 颜色通道提取

我们可以分离图片，通过不同的颜色通道提取：

```python
b,g,r=cv2.split(img)
```

这是效果：1，2，3分别代表b,g,r

当然也可以合回去：

```python
img=cv2.merge(b,g,r)
```

我们也可以单独保留，直接修改：

```python
#只保留R
cur_img=img.copy()
cur_img[:,:,0]=0
cur_img[:,:,1]=0
cv2.imshow('1',cur_img)
```

###### 边界填充

我们可以扩充图像，通过一些方式来对图像进行扩充：请看这里：

```python
top_size,bottom_size,left_size,right_size=(50,50,50,50)

replicate=cv2.copyMakeBorder(img,top_size,bottom_size,left_size,right_size,borderType=cv2.BORDER_REPLICATE)


reflect=cv2.copyMakeBorder(img,top_size,bottom_size,left_size,right_size,borderType=cv2.BORDER_REFLECT)


reflect101=cv2.copyMakeBorder(img,top_size,bottom_size,left_size,right_size,borderType=cv2.BORDER_REFLECT_101)


wrap=cv2.copyMakeBorder(img,top_size,bottom_size,left_size,right_size,borderType=cv2.BORDER_WRAP)



constant=cv2.copyMakeBorder(img,top_size,bottom_size,left_size,right_size,borderType=cv2.BORDER_CONSTANT,value=0)
```

​    我们得到了五张图像，随后，我们使用imwrite输出图像，同时导入matplotlib的pyplot子库进行观察：

​    这是总的效果：

​     仔细观察：

​    第一张图是展示了

​    replicate：这个单词是复制的意思：直接复制最边缘的像素

​    reflect：对感兴趣的部分进行两边复制：fedcba|abcdef|fedcba

​    reflect101:但是是对最边缘的像素为对称轴进行复制:gfedcba|abcdefgh|gfedcba

​    wrap:外包装：cdefgh|abcdefgh|abcdefg

​    constant:对图像以默认黑值填充

###### 对图像进行数值操作

​    我们可以对numpy进广播操作。人话翻译成C++就是cv2库重载了运算符号，使之我们可以对矩阵进行广义的加法：

```python
img_cat=cv2.imread('cat.jpg')
img_cat_GeneralAdd=img_cat+10;
img_cat[:5,:,0]
img_cat2[:5,:,0]
```

​    在控制台上输出就可以发现矩阵里每一个数值都加上了一个10。

​    （懒得自己跑，截个图）

​    那可不可以狭义相加呢？当然可以，结合线性代数的常识，相加的矩阵必须满足大小完全一致。假设我们已经满足了这个前提，直接相加得到的结果是不是就是放到矩阵的值呢？

​    显然不是！因为RGB有界，不可以超过255.在重载的+中，矩阵的RGB值自动%256，就是除以2256取它的余数放到矩阵里。那还有别的加法吗？有：使用方法add，传入cv2.add(img_cat,img_cat2)就可以了，达到255之后就不会取模，只会停在255不动

###### 图像叠加

​    我们也可以对图像进行叠加。但是注意，我们首先要调整图像大小一致：

```python
img_cat.shape
img_dog=imread(path)# path是路径
img_dog=cv2.resize(img_dog,(/*size required to resize*/))
```

​    同样的还有其他resize方法：

```python
required_pic=cv2.resize(img_required_resize,(0,0),fx=1,fy=3)
```

​    这是个什么玩意呢？指的是我们依照某个点把图像在X轴上拉长3倍数，Y轴不变。

​    现在，我们使用addWeighted来叠加图像，以混合图片特征。

```python
res=cv2.addWeighted(img_cat,0.4,img_dog,0.6,0)
#img_cat*0.4+img_dog*0.6+0//最后一项是亮度提升
```

###### 图像阈值

​    我们可以使用一些参数，对图像进行有条件的处理

```python
ret,dst=cv2.threshold(src,thresh,maxval,type)
```

src:输入，只能输入单通道图像，通常是灰度图

dst：输出图

thresh:执行阈值

maxval:超过或小于阈值后所赋予的值

type:方法，如下：

1.cv2.THRESH_BINARY：超过阈值的取maxval,否则取0

2.cv2.THRESH_BINARY_INV反过来

3.THRESH_TRUNC大于阈值的设置成阈值

4.THRESH_TOZERO大于阈值的不变，否则设置成0

5.THRESH_TOZERO_INV反转

我们依旧使用matplotlib的pyplot库放送一下

```python
import cv2
import matplotlib.pyplot as plt
img=cv2.imread('2.png')
ret,thresh1=cv2.threshold(img,127,255,cv2.THRESH_BINARY)
ret,thresh2=cv2.threshold(img,127,255,cv2.THRESH_BINARY_INV)
ret,thresh3=cv2.threshold(img,127,255,cv2.THRESH_TRUNC)
ret,thresh4=cv2.threshold(img,127,255,cv2.THRESH_TOZERO)
ret,thresh5=cv2.threshold(img,127,255,cv2.THRESH_TOZERO_INV)
titles=['Original Image','BINARY','BINARY_INV','THRESH_TRUNC','TOZERO','TOZERO_INV']
images=[img,thresh1,thresh2,thresh3,thresh4,thresh5]
for i in range(6):
    plt.subplot(2,3,i+1),plt.imshow(images[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
```

# Opencv in Pycharm(2)

## 		图像处理

### 平滑操作

​		平滑平滑，取平均。我们使用卷积核来处理图像像素点。

​		针对上面这个噪点图形，我们应用平均卷积操作。我们对噪点抹除，就是通过对周围像素点取平均。我们首先构造一个3$\times$3的矩阵对目标像素点为中心的内核求取内积。（不同于经典矩阵相乘，我们是一一对应的，平凡算法复杂度为$O(N^k)(k \in N^+)$的相乘）随后把结果填充到像素点的中心。

​		下面我们对这个图操作一下：

```python
img_path = "img/lenaNoise.png"
img = cv2.imread(img_path)
cv2.imshow("Noise Version",img)
blur33=cv2.blur(img,(3,3))
cv2.imshow("3 times 3",blur33)
blur55=cv2.blur(img,(5,5))
cv2.imshow("3 times 3",blur55)
cv2.waitKey(0)
```

​		产生的效果是令人满意的：

​		可以看到核越大，越是噪点不明显，但是图像也就越模糊。

​		还有一个类似的：是BoxFilter函数：（方框滤波）

​		在OpenCV中，实现方框滤波的函数是cv2.boxFilter（），其语法格式为：

```python
    dst=cv2.boxFilter（src,ddepth,ksize,anchor,normalize,borderType）
    # 但是一般的。。。。。。
	dst=cv2.boxFilter（src,ddepth,ksize）
```

	● dst是返回值，表示进行方框滤波后得到的处理结果。
	● src 是需要处理的图像，即原始图像。它能够有任意数量的通道，并能对各个通道独立处理。图像深度应该是CV_8U、CV_16U、CV_16S、CV_32F 或者 CV_64F中的一种。
	 ● ddepth是处理结果图像的图像深度，一般使用-1表示与原始图像使用相同的图像深度。
	 ● ksize 是滤波核的大小。滤波核大小是指在滤波处理过程中所选择的邻域图像的高 度和宽度。
	● anchor 是锚点，其默认值是（-1,-1），表示当前计算均值的点位于核的中心点位 置。该值使用默认值即可，在特殊情况下可以指定不同的点作为锚点。
	● normalize 表示在滤波时是否进行归一化（这里指将计算结果规范化为当前像素值范围内的值）处理，该参数是一个逻辑值，可能为真（值为1）或假（值为0）：
	1.当参数normalize=1时，表示要进行归一化处理，要用邻域像素值的和除以面积。此时方框滤波与均值滤波效果相同。
	2.当参数normalize=0时，表示不需要进行归一化处理，直接使用邻域像素值的和。当 normalize=0时，因为不进行归一化处理，因此滤波得到的值很可能超过当前像素值范围的最大值，从而被截断为最大值。这样，就会得到一幅纯白色的图像。
	● borderType是边界样式，该值决定了以何种方式处理边界。
	通常情况下，在使用方框滤波函数时，对于参数anchor、normalize和borderType，直接采用其默认值即可。因此，函数cv2.boxFilter（）的常用形式为：

​		可以等效成blur，就是选择更多了而已。如果不进行归一化，就是停在255，所以图像会很白。

```python
Filt1 = cv2.boxFilter(img,-1,(3,3),normalize=True)
Filt2 = cv2.boxFilter(img,-1,(3,3),normalize=False)
cv2.imshow("Filt1",Filt1);
cv2.imshow("Filt2",Filt2);
cv2.imwrite("Filt1.png",Filt1)
cv2.imwrite("Filt2.png",Filt2)
cv2.waitKey(0)
```

#### 高斯滤波

​		这个改进了平均算法，就是利用空间距离远近来作为计算权重：近的权重大，反之权重小。

```python
Gaussain=cv2.GaussianBlur(img,(5,5),1)
cv2.imshow("Gaussain",Gaussain)
cv2.imwrite("Gaussain.png",Gaussain)
```

##### 关于高斯滤波及其算法的扩展

材料来源：[(46条消息) opencv-------高斯滤波_opencv高斯滤波_LYSSLQ2015的博客-CSDN博客](https://blog.csdn.net/LYSSLQ2015/article/details/125110610)！

​		高斯滤波(Gauss Filter)是**线性滤波**中的一种。在OpenCV图像滤波处理中，高斯滤波用于**平滑图像**，或者说是图像模糊处理，因此高斯滤波是低通的。其广泛的应用在图像处理的减噪过程中，尤其是被高斯噪声所污染的图像上。高斯滤波的基本思想是: 图像上的每一个像素点的值，都由其本身和邻域内其他像素点的值经过加权平均后得到。其具体操作是，用一个核(又称为卷积核、掩模、矩阵)扫描图像中每一个像素点，将邻域内各个像素值与对应位置的权值相称并求和。从数学的角度来看，高斯滤波的过程是图像与高斯正态分布做卷积操作。
​		注意: 高斯滤波是将二维高斯正态分布放在图像矩阵上做卷积运算。考虑的是邻域内像素值的空间距离关系，因此对彩色图像处理时应分通道进行操作，也就是说操作的图像原矩阵时用单通道数据，最后合并为彩色图像。

一、几个概念

1. 什么是[低通滤波](https://so.csdn.net/so/search?q=低通滤波&spm=1001.2101.3001.7020)、平滑图像、图像模糊处理？
   平滑图像与图像模糊处理是相同的含义。平滑处理即是通过操作后，使得图像的像素值与邻域内其他像素值的的变化程度减小。在一张图像上，边缘的像素值是变化程度最剧烈的地方，而其他相对平缓。因此，平滑图像最直观的表现是图像的上物体的边缘轮廓变得模糊。**低通滤波是指仅允许低频率信号通过。一张图像上的大部分能量聚集在低频和中频上，而高频大多是图像中物体的边缘部分，也有可能是高频噪声点。在单通道中，各像素点的取值都在(0~255)中，因此，低通滤波通过一定的阙值设置，有去除高频信号和平缓边缘的效果。**

2. 什么是核(又称为卷积核、掩模、矩阵)？
   **核的本质其实就是一个大小固定、由数值参数组成的数学矩阵，例如一个3*3的核就是一个3*3的矩阵,而矩阵中的数据则为权值。**

3. 什么是卷积运算？
   卷积运算是指输入图像中某一像素点的邻域的各个值（包括该点）与卷积算子中的值做矩阵相乘运算，最后得到输出值。
   卷积算子的公式:

![这里写图片描述](https://img-blog.csdn.net/20180501112658771?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](https://img-blog.csdn.net/20180501112710588?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

g(i，j) 代表原图像矩阵上的(i，j)点的值，它是输出值。
f(i-k，j-l) 代表原图像矩阵上(i，j)点的邻域中的对应点的值。
h(k,，l) 代表与f(i-k ， j-l)这个值在核对应位置的点的值
**请看下图：这里用的是f(i-k,j-l)h(k,l)**

![这里写图片描述](https://img-blog.csdn.net/20180501192707205?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)



由上图我们看到，矩阵f是将要进行操作的图像矩阵，当前的(i，j)是(2，2)点。h为核，其以中心(0，0)为参考点。因此f矩阵对应范围即为f(2，2)的邻域。矩阵g为图像输出矩阵，g(2，2)的值为输出值。
注意：卷积算子和相关算子在核上是180度翻转的矩阵，请不要搞混

4.核(卷积核、掩模、矩阵等)
在3的卷积运算中，用到的公式是：
g(i, j) = ∑ f(i-k, j-l)h(k, l) 。其中 k，l代表核上的坐标。而核的坐标明显与数组下标不一致。因此，我们需要做一个转换以满足用数组下标来访问该核的数据。
假设有3*3数组a，它与核的对应关系为
a(0, 0) ===> h(-1, -1) a(0, 1) ===> h(-1, 0) a(0, 2) ===> h(-1, 1)
a(1, 0) ===> h(0, -1) a(1, 1) ===> h(0, 0) a(1, 2) ===> h(0, 1)
a(2, 0) ===> h(1, -1) a(2, 1) ===> h(1, 0) a(2, 2) ===> h(1, 1)
对于3*3数组，其下标是0开始的，假设该数组的参考点(ai, aj)为中心,则有
g(i, j) = ∑ f(i-(k-ai), j-(l-aj))h(k, l)
带入数组参考点(1, 1)，则有
g(i, j) = ∑ f(i-(k-1), j-(l-1))h(k, l)
此时，k，l可以从0开始取值
![这里写图片描述](https://img-blog.csdn.net/20180501195233133?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

 **5.图像通道分离与合并(cv::Mat)**

```c++
    // src 原图像，多通道
    // [1] 彩色图片通道分离
    std::vector<cv::Mat> channels;
    cv::split(&src, channels);
    // [3] 滤波
    // OpenCV中操作
    // channels[0]  ==>  B通道
    // channels[1]  ==>  G通道
    // channels[2]  ==>  R通道
    // 省略对各个通道的处理
    // [4] 合并返回
    cv::merge(channels, *dst);
```

#### 二、高斯函数

高斯滤波，顾名思义，这是一个建立在高斯正态分布基础上的滤波器。首先我们来了解高斯函数。(图片来源于网络)
一维高斯函数：
可以看到，G(x)的跟[sigma](https://so.csdn.net/so/search?q=sigma&spm=1001.2101.3001.7020)的取值有极大的关系。sigma取值越大，图像越平缓，sigma取值越小，图像越尖锐。

![这里写图片描述](https://img-blog.csdn.net/20180501133822002?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](https://img-blog.csdn.net/20180501133859847?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

二维高斯函数：
二维高斯是构建高斯滤波器的基础。可以看到，G(x,y)在x轴y轴上的分布是一个突起的帽子的形状。这里的sigma可以看作两个值，一个是x轴上的分量sigmaX，另一个是y轴上的分量sigmaY。对图像处理可以直接使用sigma并对图像的行列操作，也可以用sigmaX对图像的行操作，再用sigmaY对图像的列操作。它们是等价的。
当sigmaX和sigmaY取值越大，整个形状趋近于扁平；当sigmaX和sigmaY取值越小，整个形状越突起。
![这里写图片描述](https://img-blog.csdn.net/20180501134156957?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](https://img-blog.csdn.net/20180501135246355?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

高斯滤波原理就是将上图的二维正态分布应用在二维的矩阵上，G(x,y)的值就是矩阵上的权值，将得到的权值进行[归一化](https://so.csdn.net/so/search?q=归一化&spm=1001.2101.3001.7020)，将权值的范围约束在[0,1]之间，并且所有的值的总和为1。
假设一个3*3的核，sigma取值1.5以及sigma取5.0，归一化后其权值分布分别是：

![这里写图片描述](https://img-blog.csdn.net/20180501172453854?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](https://img-blog.csdn.net/20180501172504760?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

假设一个5*5的核，sigma取值1.5以及sigma取5.0，经归一化后其权值分布分别是：
![这里写图片描述](https://img-blog.csdn.net/20180501172519306?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](https://img-blog.csdn.net/20180501172527684?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

可以看到，权值的分布是以中间高四周低来分布的。并且距离中心越远，其对中心点的影响就越小，权值也就越小。
因此可以总结：
（1）在核大小固定的情况下，sigma值越大，权值分布越平缓。因此，邻域各个点的值对输出值的影响越大，最终结果造成图像越模糊。
（2）在核大小固定的情况下，sigma值越小，权值分布越突起。因此，邻域各个点的值对输出值的影响越小，图像变化也越小。假如中心点权值为1，其他点权值为0，那么最终结果是图像没有任何变化。
（3）sigma固定时，核越大图像越模糊。
（4）sigma固定时，核越小图像变化越小。

三、高斯滤波器实现
首先看效果：
对于椒盐图作处理

![这里写图片描述](https://img-blog.csdn.net/20180501175404545?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

对于高斯噪声图作处理
![这里写图片描述](https://img-blog.csdn.net/20180501175434142?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3FxXzM2MzU5MDIy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

（1）main函数：读取图片 ==> 高斯滤波 ==> 结果显示

```cpp
int main()
{
    // [1] src读入图片
    cv::Mat src = cv::imread("Median_pic.jpg");
    // [2] dst目标图片
    cv::Mat dst;
    // [3] 高斯滤波  sigma越大越平越模糊
    myGaussianFilter(&src, &dst, 5, 1.5f);
    // [4] 窗体显示
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
```

（2）彩色图像通道分离处理，每个通道都进行高斯滤波，最后合并

```C++
void myGaussianFilter(cv::Mat *src, cv::Mat *dst, int n, double sigma)
{
    // [1] 初始化
    *dst = (*src).clone();
    // [2] 彩色图片通道分离
    std::vector<cv::Mat> channels;
    cv::split(*src, channels);
    // [3] 滤波
    // [3-1] 确定高斯正态矩阵
    double **array = getGaussianArray(n, sigma);
    // [3-2] 高斯滤波处理
    for (int i = 0; i < 3; i++) {
        gaussian(&channels[i], array, n);
    }
    // [4] 合并返回
    cv::merge(channels, *dst);
    return ;
}
```

（3）生成高斯正态分布核([卷积核](https://so.csdn.net/so/search?q=卷积核&spm=1001.2101.3001.7020)，掩模等)

```C++
/* 获取高斯分布数组               (核大小， sigma值) */
double **getGaussianArray(int arr_size, double sigma)
{
    int i, j;
    // [1] 初始化权值数组
    double **array = new double*[arr_size];
    for (i = 0; i < arr_size; i++) {
        array[i] = new double[arr_size];
    }
    // [2] 高斯分布计算
    int center_i, center_j;
    center_i = center_j = arr_size / 2;
    double pi = 3.141592653589793;
    double sum = 0.0f;
    // [2-1] 高斯函数
    for (i = 0; i < arr_size; i++ ) {
        for (j = 0; j < arr_size; j++) {
            array[i][j] = 
                //后面进行归一化，这部分可以不用
                //0.5f *pi*(sigma*sigma) * 
                exp( -(1.0f)* ( ((i-center_i)*(i-center_i)+(j-center_j)*(j-center_j))/ (2.0f*sigma*sigma) ));                                    			sum += array[i][j];
        }
    }
    // [2-2] 归一化求权值
    for (i = 0; i < arr_size; i++) {
        for (j = 0; j < arr_size; j++) {
            array[i][j] /= sum;
            printf(" [%.15f] ", array[i][j]);
        }
        printf("\n");
    }
    return array;
}
```

（4）进行高斯滤波操作

```C++
/* 高斯滤波 (待处理单通道图片, 高斯分布数组， 高斯数组大小(核大小) ) */
void gaussian(cv::Mat *_src, double **_array, int _size)
{
    cv::Mat temp = (*_src).clone();
    // [1] 扫描
    for (int i = 0; i < (*_src).rows; i++) {
        for (int j = 0; j < (*_src).cols; j++) {
            // [2] 忽略边缘
            if (i > (_size / 2) - 1 && j > (_size / 2) - 1 &&
                i < (*_src).rows - (_size / 2) && j < (*_src).cols - (_size / 2)) {
                // [3] 找到图像输入点f(i,j),以输入点为中心与核中心对齐
                //     核心为中心参考点 卷积算子=>高斯矩阵180度转向计算
                //     x y 代表卷积核的权值坐标   i j 代表图像输入点坐标
                //     卷积算子     (f*g)(i,j) = f(i-k,j-l)g(k,l)          f代表图像输入 g代表核
                //     带入核参考点 (f*g)(i,j) = f(i-(k-ai), j-(l-aj))g(k,l)   ai,aj 核参考点
                //     加权求和  注意：核的坐标以左上0,0起点
                double sum = 0.0;
                for (int k = 0; k < _size; k++) {
                    for (int l = 0; l < _size; l++) {
                        sum += (*_src).ptr<uchar>(i-k+(_size/2))[j-l+(_size/2)] * _array[k][l];
                    }
                }
                // 放入中间结果,计算所得的值与没有计算的值不能混用
                temp.ptr<uchar>(i)[j] = sum;
            }
        }
    }
    // 放入原图
    （*_src） = temp.clone();
}
```

### 中值滤波

​		什么是中值？就是排序取中间的中位数。那就直接把目标像素点直接换成中位数跑路！

```python
median=cv2.medianBlur(img,5)
cv2.imshow("median",median)
cv2.imwrite("median.png",median)
```

​		![median](C:\Users\陈冠豪\Desktop\My coding repositary\Pycharm project\opencv pyhton\3\median.png)

​		可以看到效果很好。令人满意。

#### 扩展阅读

		一、概述
	    使用中值滤波器模糊图像。
	
	    该函数使用具有 ksize×ksize 孔径的中值滤波器对图像进行平滑处理。 多通道图像的每个通道都是独立处理的。
	
	    中值滤波器在内部使用 BORDER_REPLICATE 来处理边界像素，请参阅 BorderTypes。
	
	    下图描述了一个ksize=3×3的滑动窗口（或称滤波器模板、kernel），如黄色部分所示。用这个ksize=3×3的窗口作用于原始图像上的每一个像素，如下图的绿色部分所示，被这个窗口覆盖的9个像素点都参与计算，这样在该像素点上就会得到一个新的像素值，当窗口沿着图像逐个像素进行计算，就会得到一幅新的图像。

![img](https://img-blog.csdnimg.cn/9f8842b4f8da4836a54e1b6a66ab13fa.png)

         上图中滤波器模板的不同就构成了滤波算法的差异，比如均值平滑算法中滑动窗口中各个像素点的系数均为1/(窗口高*窗口宽)，高斯平滑中系数和中心点的距离满足高斯分布。
    
        中值平滑和均值平滑一样也用到了滑动窗口，但是它并不是计算滑动窗口中的某种加权和，而是使用原图像滑动窗口中所有像素值排序后的中值作为新图像的像素值。
    
        从上图也可以看到，当滑动窗口作用于图像边沿的时候，滑动窗口的某些像素并没有和图像重合，这时就需要对边沿做特殊处理，常用的方法有填0、填1、复制边沿等方式。

二、medianBlur函数
1、函数原型
cv::medianBlur (InputArray src, OutputArray dst, int ksize)
2、参数详解
src	：输入 1、3 或 4 通道图像； ksize 为 3 或 5 时，图像深度应为 CV_8U、CV_16U 或 CV_32F，对于较大的光圈尺寸，只能为 CV_8U。

dst	：与 src 大小和类型相同的目标数组。

ksize	：孔径线性尺寸； 它必须是奇数且大于 1，例如：3、5、7 ...
三、OpenCV源码
1、源码路径

```
opencv\modules\imgproc\src\median_blur.dispatch.cpp
```

2、源码代码

```C++
void medianBlur( InputArray _src0, OutputArray _dst, int ksize )
{
    CV_INSTRUMENT_REGION();
	CV_Assert(!_src0.empty());
 
	CV_Assert( (ksize % 2 == 1) && (_src0.dims() <= 2 ));
 
	if( ksize <= 1 || _src0.empty() )
	{
   		_src0.copyTo(_dst);
    	return;
	}
 
	CV_OCL_RUN(
				_dst.isUMat(),
         		ocl_medianFilter(_src0,_dst, ksize)
         		)
 
	Mat src0 = _src0.getMat();
	_dst.create( src0.size(), src0.type() );
	Mat dst = _dst.getMat();
 
	CALL_HAL(
	medianBlur, 
	cv_hal_medianBlur, 
	src0.data, 
	src0.step, 	
	dst.data, 
	dst.step, 
	src0.cols, 
	src0.rows, 
	src0.depth(),
    src0.channels(), ksize
    );
 
	CV_OVX_RUN(true,
           		openvx_medianFilter(_src0, _dst, ksize))
 
	//CV_IPP_RUN_FAST(ipp_medianFilter(src0, dst, ksize));
 
	CV_CPU_DISPATCH(
	medianBlur, 
	(src0, dst, ksize),
    CV_CPU_DISPATCH_MODES_ALL
    );
}
```

四、效果图像示例

原图：

![img](https://img-blog.csdnimg.cn/7a3c9fa7cb44463cb9c29ea0e1def515.png)

![img](https://img-blog.csdnimg.cn/9d19f5513c46421094abc1e260e2352d.png)

![img](https://img-blog.csdnimg.cn/9173c63503904f4eb03c876c4048cfa1.png)

版权声明：本文为CSDN博主「坐望云起」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/bashendixie5/article/details/125255049

### 图像拼接

​		现在我们使用Numpy的hstack方法拼接一下图片：

```python
res=np.hstack((blur33,Gaussain,median))
cv2.imshow("Compare!",res)
cv2.imwrite("Compare.png",res)
```

### 腐蚀操作

​		对于这样的一些图片：

​		我们可以使用腐蚀操作来钝化特征：删除掉一些边界的像素点（置黑色）。其中：腐蚀的大小，范围是由kernel决定的。在Python中，我们需要这样指定一个核：

```python
kernel=np.ones((5,5),np.uint8)
```

​		还是需要指定一个迭代次数的参数，这行代码完成了这样的工作：

```python
erosion=cv2.erode(img,
                  kernel,
                  iterations=1)#迭代次数
```

我们首先看看效果怎么样：

​		可以看到，腐蚀核在检测到边界条件的时候（白转黑and黑转白）自动将这些像素点填充成黑色，除非核内的像素点都是统一的，否则都会腐蚀！

​		可以来点控制变量！比如说指定不同的腐蚀核来观察效果

```python
import cv2
import numpy as np
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
kernel55=np.ones((5,5),np.uint8)
erosion33=cv2.erode(img,kernel33,iterations=1)
erosion55=cv2.erode(img,kernel55,iterations=1)
res=np.hstack((img,erosion33,erosion55))
cv2.imshow("comp",res)
cv2.imwrite("Kernel Diff compararison.png",res)
cv2.waitKey(0)
```

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
kernel55=np.ones((5,5),np.uint8)
erosion33=cv2.erode(img,kernel33,iterations=1)
erosion55=cv2.erode(img,kernel55,iterations=1)
imgs_ero1=[img,erosion33,erosion55]
titles=['Original','3 times 3 ','5 times t ']
for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(imgs_ero1[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
```

​		可以看到，核越大，就越会腐蚀图像！

​		下面看看图像迭代影响：

```python
import cv2
import numpy as np
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
erosion1=cv2.erode(img,kernel33,iterations=1)
erosion2=cv2.erode(img,kernel33,iterations=2)
res=np.hstack((img,erosion1,erosion2))
cv2.imshow("comp",res)
cv2.imwrite("Iterator Diff comparasion.png",res)
cv2.waitKey(0)
```

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
erosion1=cv2.erode(img,kernel33,iterations=1)
erosion2=cv2.erode(img,kernel33,iterations=2)
imgs_ero1=[img,erosion1,erosion2]
titles=['Original','1 ','2 ']
for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(imgs_ero1[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
```

可以看见：越是迭代，图像腐蚀的越严重！

### 膨胀

​		这个操作可以视作腐蚀操作的反操作：就是将特征明显化：

​		老规矩：还是看看改变核大小和迭代次数产生的效果如何：

​		先看核大小：

```python
import cv2
import numpy as np
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
kernel55=np.ones((5,5),np.uint8)
dilate1=cv2.dilate(img,kernel33,iterations=1)
dilate2=cv2.dilate(img,kernel55,iterations=1)
res=np.hstack((img,dilate1,dilate2))
cv2.imshow("comp",res)
cv2.imwrite("kernel_in_dilate Diff comparasion.png",res)
```

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
kernel55=np.ones((5,5),np.uint8)
dilate1=cv2.dilate(img,kernel33,iterations=1)
dilate2=cv2.dilate(img,kernel55,iterations=1)
titles=['org','3 times 3','5 times 5']
img_group=[img,dilate1,dilate2]
for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(img_group[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
```

​		再来看看迭代器的影响：

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path="1.png"
img=cv2.imread(path)
kernel33=np.ones((3,3),np.uint8)
dilate1=cv2.dilate(img,kernel33,iterations=1)
dilate2=cv2.dilate(img,kernel33,iterations=2)
titles=['org','3 times 3','5 times 5']
img_group=[img,dilate1,dilate2]
for i in range(3):
    plt.subplot(1,3,i+1),plt.imshow(img_group[i],'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])
plt.show()
```

​		还是很容易看出来：核越大，迭代次数越多，图片的特征就被放大的越明显！

#### 扩展阅读1

​		版权声明：本文为CSDN博主「我有一個夢想」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
​		原文链接：https://blog.csdn.net/B08370108/article/details/118028678



​		**图像的腐蚀过程与图像的卷积操作类似，都需要模板矩阵来控制运算的结果**，在图像的腐蚀和膨胀中这个模板矩阵被称为结构元素。与图像卷积相同，结构元素可以任意指定图像的中心点，并且结构元素的尺寸和具体内容都可以根据需求自己定义。定义结构元素之后，将结构元素的中心点依次放到图像中每一个非0元素处，如果此时结构元素内所有的元素所覆盖的图像像素值均不为0，则保留结构元素中心点对应的图像像素，否则将删除结构元素中心点对应的像素。图像的腐蚀过程示意图如图6-12所示，图6-12中左侧为待腐蚀的原图像，中间为结构元素，**首先将结构元素的中心与原图像中的A像素重合，此时结构元素中心点的左侧和上方元素所覆盖的图像像素值均为0，因此需要将原图像中的A像素删除**；**当把结构元素的中心点与B像素重合时，此时结构元素中所有的元素所覆盖的图像像素值均为1**，因此保留原图像中的B像素。将结构元素中心点依次与原图像中的每个像素重合，判断每一个像素点是否保留或者删除，最终原图像腐蚀的结果如图中下侧图像所示。

​		![img](https://img-blog.csdnimg.cn/2021011613033220.png)

​		图像腐蚀可以用“Θ”表示，其数学表示形式如式(6.4)所示，通过公式可以发现，其实对图像A的腐蚀运算就是寻找图像中能够将结构元素B全部包含的像素点。

​		生成常用的矩形结构元素、十字结构元素和椭圆结构：

```C++
Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));
```

```C++
//shape：结构元素的种类，可以选择的参数及含义在表6-5中给出。
//ksize：结构元素的尺寸大小
//anchor：中心点的位置，默认参数为结构元素的几何中心点。
```

 		该函数用于生成图像形态学操作中常用的矩形结构元素、十字结构元素和椭圆结构元素。函数第一个参数为生成结构元素的种类，可以选择的参数及含义在表给出，函数第二个参数是结构元素的尺寸大小，能够影响到图像腐蚀的效果，一般情况下，结构元素的种类相同时，结构元素的尺寸越大腐蚀效果越明显。函数的最后一个参数是结构元素的中心点，只有十字结构元素的中心点位置会影响图像腐蚀后的轮廓形状，其他种类的结构元素的中心点位置只影响形态学操作结果的平移量。

![表6-5 getStructuringElement()函数结构元素形状可选择参数](https://img-blog.csdnimg.cn/20210116131530359.png#pic_center)

腐蚀函数

```C++
void erode( InputArray src, 
           OutputArray dst, 
           InputArray kernel,
           Point anchor = Point(-1,-1), int iterations = 1,
           int borderType = BORDER_CONSTANT,
           const Scalar& borderValue = morphologyDefaultBorderValue() 
          );
```

```C++
//src：输入的待腐蚀图像，图像的通道数可以是任意的，但是图像的数据类型必须是CV_8U，CV_16U，CV_16S，CV_32F或CV_64F之一。
//dst：腐蚀后的输出图像，与输入图像src具有相同的尺寸和数据类型。
//kernel：用于腐蚀操作的结构元素，可以自己定义，也可以用getStructuringElement()函数生成。
//anchor：中心点在结构元素中的位置，默认参数为结构元素的几何中心点
//iterations：腐蚀的次数，默认值为1。
//borderType：像素外推法选择标志，取值范围在表3-5中给出。默认参数为BORDER_DEFAULT，表示不包含边界值倒序填充。
//borderValue：使用边界不变外推法时的边界值。
```

​		该函数根据结构元素对输入图像进行腐蚀，在腐蚀多通道图像时每个通道独立进行腐蚀运算。
​		函数的第一个参数为待腐蚀的图像，图像通道数可以是任意的，但是图像的数据类型必须是CV_8U，CV_16U，CV_16S，CV_32F或CV_64F之一。
​		函数第二个参数为腐蚀后的输出图像，与输入图像具有相同的尺寸和数据类型。
​		函数第三个和第四个参数都是与结构元素相关的参数，第三个参数为结构元素，第四个参数为结构元素的中心位置，第四个参数的默认值为Point(-1,-1)，表示结构元素的几何中心处为结构元素的中心点。
​		函数第五个参数是使用结构元素腐蚀的次数，腐蚀次数越多效果越明显，参数默认值为1，表示只腐蚀1次。
​		函数第六个参数是图像像素外推法的选择标志，
​		第七个参数为使用边界不变外推法时的边界值，这两个参数对图像中主要部分的腐蚀操作没有影响，因此在多数情况下使用默认值即可。

​		需要注意的是该函数的腐蚀过程只针对图像中的非0像素，因此如果图像是以0像素为背景，那么腐蚀操作后会看到图像中的内容变得更瘦更小；如果图像是以255像素为背景，那么腐蚀操作后会看到图像中的内容变得更粗更大。

```C++
   简单示例

//
// Created by smallflyfly on 2021/6/18.
//

#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

void drawResult(Mat im, int num, Mat stats, Mat centroids, const string& name) 
{
    for (int i = 1; i < num; ++i) 
    {
        int x = centroids.at<double>(i, 0);
        int y = centroids.at<double>(i, 1);
        cout << x << " " << y << endl;
        circle(im, Point(x, y), 2, Scalar(0, 0, 255), -1);
        int xmin = stats.at<int>(i, CC_STAT_LEFT);
        int ymin = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);
		Rect rect(xmin, ymin, w, h);
    	rectangle(im, rect, Scalar(255, 255, 255), 2);
    	putText(
            	im, 
                to_string(i), 
                Point(x+5, y), 
                FONT_HERSHEY_SCRIPT_SIMPLEX, 
                0.3, 
                Scalar(0, 0, 255), 
                1);
	}
	imshow(name, im);
}


int main() {
Mat src = (
            Mat_<uchar>(6, 6) <<
                    0, 0, 0, 0, 255, 0,
                    0, 255, 255, 255, 255, 255,
                    0, 255, 255, 255, 255, 0,
                    0, 255, 255, 255, 255, 0,
                    0, 255, 255, 255, 255, 0,
                    0, 0, 0, 0, 255, 0
        );
resize(src, src, Size(0, 0), 50, 50, INTER_NEAREST);
Mat m1, m2;
m1 = getStructuringElement(0, Size(3, 3));
m2 = getStructuringElement(1, Size(3, 3));
 
Mat erodeM1, erodeM2;
erode(src, erodeM1, m1, Point(-1, -1), 10);
erode(src, erodeM2, m2, Point(-1, -1), 10);
 
imshow("src", src);
imshow("erodeM1", erodeM1);
imshow("erodeM2", erodeM2);
 
Mat xbim = imread("xiaobai.jpg");
Mat xbM1, xbM2;
erode(xbim, xbM1, m1, Point(-1, -1), 2);
erode(xbim, xbM2, m2, Point(-1, -1), 2);
 
imshow("xb", xbim);
imshow("xbM1", xbM1);
imshow("xbM2", xbM2);
 
Mat im = imread("rice.jfif");
Mat im1 = im.clone();
Mat im2 = im.clone();
Mat im3 = im.clone();
 
Mat gray;
cvtColor(im, gray, CV_BGR2GRAY);
Mat riceBin;
threshold(gray, riceBin, 125, 255, THRESH_BINARY);
 
Mat out, stats, centroids;
int count1 = connectedComponentsWithStats(riceBin, out, stats, centroids, 8, CV_16U);
drawResult(im1, count1, stats, centroids, "no erode");
 
Mat erodeIm1, erodeIm2;
erode(riceBin, erodeIm1, m1, Point(-1, -1), 5);
erode(riceBin, erodeIm2, m2, Point(-1, -1), 5);
 
int count2 = connectedComponentsWithStats(erodeIm1, out, stats, centroids, 8, CV_16U);
drawResult(erodeIm1, count2, stats, centroids, "erode1");
int count3 = connectedComponentsWithStats(erodeIm2, out, stats, centroids, 8, CV_16U);
drawResult(erodeIm2, count3, stats, centroids, "erode2");
 
waitKey(0);
destroyAllWindows();
}
```

![img](https://img-blog.csdnimg.cn/20210618162305913.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0IwODM3MDEwOA==,size_16,color_FFFFFF,t_70)

#### 扩展阅读2

​		版权声明：本文为CSDN博主「我有一個夢想」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
​		原文链接：https://blog.csdn.net/B08370108/article/details/118029682

​		图像的膨胀与图像腐蚀是一对相反的过程，与图像腐蚀相似，图像膨胀同样需要结构元素用于控制图像膨胀的效果。结构元素可以任意指定结构的中心点，并且结构元素的尺寸和具体内容都可以根据需求自己定义。**定义结构元素之后，将结构元素的中心点依次放到图像中每一个非0元素处，如果原图像中某个元素被结构元素覆盖，但是该像素的像素值不与结构元素中心点对应的像素点的像素值相同，那么将原图像中的该像素的像素值修改为结构元素中心点对应点的像素值。**图像的膨胀过程示意图如图所示，图中左侧为待膨胀的原图像，中间为结构元素，首先将结构元素的中心与原图像中的A像素重合，将结构元素覆盖的所有像素的像素值都修改为1，将结构元素中心点依次与原图像中的每个像素重合，判断是否有需要填充的像素。原图像膨胀的结果如图中右侧图像所示。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210117230235852.png)

 		图像膨胀数学表示形式如式(6.5)所示，通过公式可以发现，其实图像A的膨胀运算就是生成能够将结构元素B全部包含的图像。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210117230534606.png)

膨胀函数

```
void dilate( 
	InputArray src, 
	OutputArray dst, 
	InputArray kernel,
	Point anchor = Point(-1,-1), int iterations = 1,
	int borderType = BORDER_CONSTANT,
	const Scalar& borderValue = morphologyDefaultBorderValue() 
);
```

```C++
//src：输入的待膨胀图像，图像的通道数可以是任意的，但是图像的数据类型必须是CV_8U，CV_16U，CV_16S，CV_32F或CV_64F之一。
//dst：膨胀后的输出图像，与输入图像src具有相同的尺寸和数据类型。
//kernel：用于膨胀操作的结构元素，可以自己定义，也可以用getStructuringElement()函数生成。
//anchor：中心点在结构元素中的位置，默认参数为结构元素的几何中心点
//iterations：膨胀的次数，默认值为1。
//borderType：像素外推法选择标志，取值范围在表3-5中给出。默认参数为BORDER_DEFAULT，表示不包含边界值倒序填充。
//borderValue：使用边界不变外推法时的边界值
```


 		该函数根据结构元素对输入图像进行膨胀，在膨胀多通道图像时每个通道独立进行膨胀运算。函数的第一个参数为待膨胀的图像，图像通道数可以是任意的，但是图像的数据类型必须是CV_8U，CV_16U，CV_16S，CV_32F或CV_64F之一。

​		函数第二个参数为膨胀后的输出图像，与输入图像具有相同的尺寸和数据类型。函数第三个和第四个参数都是与结构元素相关的参数，

​		第三个参数为结构元素，膨胀时使用的结构元素尺寸越大效果越明显，第四个参数为结构元素的中心位置，

​		第四个参数的默认值为Point(-1,-1)，表示结构元素的几何中心处为结构元素的中心点。

​		函数第五个参数是使用结构元素膨胀的次数，膨胀次数越多效果越明显，默认参数为1，表示只膨胀1次。

​		函数第六个参数是图像像素外推法的选择标志，

​		第七个参数为使用边界不变外推法时的边界值，这两个参数对图像中主要部分的膨胀操作没有影响，因此在多数情况下使用默认值即可。

```C++
    简单示例

//
// Created by smallflyfly on 2021/6/18.
//

#include "opencv2/opencv.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void drawResult(Mat im, int num, Mat stats, Mat centroids, const string& name) {
    for (int i = 1; i < num; ++i) {
        int x = centroids.at<double>(i, 0);
        int y = centroids.at<double>(i, 1);
        cout << x << " " << y << endl;
        circle(im, Point(x, y), 2, Scalar(0, 0, 255), -1);
        int xmin = stats.at<int>(i, CC_STAT_LEFT);
        int ymin = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);
    	Rect rect(xmin, ymin, w, h);
   		rectangle(im, rect, Scalar(255, 255, 255), 2);
    	putText(
    	im, 
    	to_string(i), 
    	Point(x+5, y), 
    	FONT_HERSHEY_SCRIPT_SIMPLEX, 
    	0.3,
        Scalar(0, 0, 255), 
        1);
	}
	imshow(name, im);
}

int main() {
    Mat src = (
            Mat_<uchar>(6, 6) <<
                              0, 0, 0, 0, 255, 0,
                    0, 255, 255, 255, 255, 255,
                    0, 255, 255, 255, 255, 0,
                    0, 255, 255, 255, 255, 0,
                    0, 255, 255, 255, 255, 0,
                    0, 0, 0, 0, 255, 0
    );
    resize(src, src, Size(0, 0), 50, 50, INTER_NEAREST);
    Mat m1, m2;
    m1 = getStructuringElement(0, Size(3, 3));
    m2 = getStructuringElement(1, Size(3, 3));
Mat dilateM1, dilateM2;
dilate(src, dilateM1, m1, Point(-1, -1), 5);
dilate(src, dilateM2, m2, Point(-1, -1), 5);
 
imshow("src", src);
imshow("dilateM1", dilateM1);
imshow("dilateM2", dilateM2);
 
Mat xbim = imread("xiaobai.jpg");
Mat xbM1, xbM2;
dilate(xbim, xbM1, m1, Point(-1, -1), 2);
dilate(xbim, xbM2, m2, Point(-1, -1), 2);
 
imshow("xbim", xbim);
imshow("xbM1", xbM1);
imshow("xbM2", xbM2);
 
Mat im = imread("rice.jfif");
resize(im, im, Size(0, 0), 0.6, 0.6);
Mat im1 = im.clone();
 
Mat gray;
cvtColor(im, gray, CV_BGR2GRAY);
Mat riceBin;
threshold(gray, riceBin, 125, 255, THRESH_BINARY);
 
Mat out, stats, centroids;
int count1 = connectedComponentsWithStats(riceBin, out, stats, centroids, 8, CV_16U);
drawResult(im, count1, stats, centroids, "no dilate");
 
Mat dilateIm1, dilateIm2;
dilate(riceBin, dilateIm1, m1, Point(-1, -1), 5);
dilate(riceBin, dilateIm2, m2, Point(-1, -1), 5);
 
int count2 = connectedComponentsWithStats(dilateIm1, out, stats, centroids, 8, CV_16U);
drawResult(dilateIm1, count2, stats, centroids, "dilateIm1");
int count3 = connectedComponentsWithStats(dilateIm2, out, stats, centroids, 8, CV_16U);
drawResult(dilateIm2, count3, stats, centroids, "dilateIm2");
 
waitKey(0);
destroyAllWindows();
```


![img](https://img-blog.csdnimg.cn/20210618165643696.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0IwODM3MDEwOA==,size_16,color_FFFFFF,t_70)

### 开运算与闭运算

​		刚刚我们整完了腐蚀和膨胀,现在我们一起用：

​		开运算指的是：**先腐蚀后膨胀**

​		闭运算指的是：**先膨胀后腐蚀**

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path = "1.png"
img = cv2.imread(path)
kernel33 = np.ones((3,3),np.uint8)
opening = cv2.morphologyEx(img,cv2.MORPH_OPEN,kernel33)
cv2.imshow("opening",opening)
closing = cv2.morphologyEx(img,cv2.MORPH_CLOSE,kernel33)
cv2.imshow("closing",closing)
cv2.imwrite("open.png",opening)
cv2.imwrite("close.png",closing)
cv2.waitKey(0)
```

### 梯度运算

​		放大边界信息！很简单：膨胀的减去腐蚀的：

```C++
import cv2
import numpy as np
from matplotlib import pyplot as plt
path = "1.png"
img = cv2.imread(path)
kernel33 = np.ones((3,3),np.uint8)
gradient=cv2.morphologyEx(img,cv2.MORPH_GRADIENT,kernel33)
cv2.imshow("gra",gradient)
cv2.imwrite("gradient.png",gradient)
cv2.waitKey(0)
```

### 礼貌与黑帽

​		**礼貌就是原始输入-开运算结果！**

​		**黑猫就是闭运算-原始输入！**

```python
import cv2
import numpy as np
from matplotlib import pyplot as plt
path = "1.png"
img = cv2.imread(path)
kernel33 = np.ones((3,3),np.uint8)
tophat=cv2.morphologyEx(img,cv2.MORPH_TOPHAT,kernel33)
blackhat=cv2.morphologyEx(img,cv2.MORPH_BLACKHAT,kernel33)
cv2.imshow("to",tophat)
cv2.imshow("bl",blackhat)
cv2.imwrite("tophat.png",tophat)
cv2.imwrite("blackhat.png",blackhat)
cv2.waitKey(0)
```



### 扩展阅读1

阅读链接：[数字图像处理(c++ opencv)：形态学图像处理-开运算与闭运算 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/541851526)

#### 开运算与闭运算

（1）开运算

原理方法：先腐蚀后膨胀；

功能作用：平滑物体轮廓、断开狭窄的狭颈、消除细长的突出和物体。

（2）闭运算

原理方法：先膨胀后腐蚀；

功能作用：弥合狭窄的狭颈或断裂处、消除小孔、填补轮廓缝隙。

```C++
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image, image_gray, image_bw;   //定义输入图像，灰度图像，二值图像
	image = imread("开运算闭运算.png");  //读取图像；
	if (image.empty())
	{
		cout << "读取错误" << endl;
		return -1;
	}
	imshow("image", image);

	//转换为灰度图像
	cvtColor(image, image_gray, COLOR_BGR2GRAY);

	//转换为二值图
	threshold(image_gray, image_bw, 120, 255, 1); //通过0，1调节二值图像背景颜色
	imshow("image_bw", image_bw);

	//闭运算
	Mat se = getStructuringElement(0, Size(3, 3)); //构造矩形结构元素
	dilate(image_bw, image_bw, se, Point(-1, -1), 5); //执行膨胀操作
	erode(image_bw, image_bw, se, Point(-1, -1), 5); //执行腐蚀操作
	
	//开运算
	//Mat se = getStructuringElement(0, Size(3, 3)); //构造矩形结构元素
	//erode(image_bw, image_bw, se, Point(-1, -1), 2); //执行腐蚀操作
	//dilate(image_bw, image_bw, se, Point(-1, -1), 2); //执行膨胀操作

	imshow("image_bw", image_bw);

	waitKey(0);  //暂停，保持图像显示，等待按键结束
	return 0;
}
```

![img](https://pic1.zhimg.com/80/v2-996d420c6bd384ca11957a8745f672b4_1440w.webp)

------

**除了使用腐蚀膨胀的函数组合来进行开运算闭运算，还可以通过opencv函数进行处理（morphologyex函数）**

### 扩展阅读2

版权声明：本文为CSDN博主「念980」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_62343847/article/details/122604497

腐蚀与膨胀

​		图像的腐蚀与膨胀互为逆向操作，通常用于处理二值图像（黑白图，以黑色为底面背景），因此需要先进行二值化处理，腐蚀和膨胀通俗的理解就是，在指定大小的卷积核内，如果该卷积核内全为黑色或全为白色，则该卷积核内像素值不变，但若是既有黑色又有白色，即在图像边缘处，那么膨胀操作则会将该卷积核内所有白色像素点都赋值变为黑色，以此将图像向内腐蚀掉一圈，而膨胀操作则相反，会将卷积核内的黑色像素点赋值成2白色，以此让图像膨胀一圈。

​		膨胀与腐蚀的函数介绍

```python
kernel = np.ones((3,3),uint8) #定义要处理的卷积核大小和卷积核的类型。
```

```python
erosion = cv2.erode(img_test3,kernel,iterations = 1) 
#对图像进行膨胀操作，img_test是要进行处理的图像，kernel是通过上一个函数定义好的卷积核，而iterations则是腐蚀操作的循环次数（可以将卷积核设置为（1，1），然后不断调整循环次数来实现精细化的腐蚀，以达到更好的腐蚀效果）。
```

```python
dilate_1 = cv2.dilate(img_test,kernel,iterations = 1)
#对图像进行膨胀操作，这里的参数跟上面的参数作用一样，只是改了函数名而已。（同样可以将卷积核设置为（1，1），不断改变循环次数，以达到更好的膨胀效果）。
```

​		应用：腐蚀操作一般用于消去图像中不需要的粘连部分，而膨胀操作则用于填充图像内的空白部分，同时也可以恢复图像由于进行腐蚀操作后缩小的面积，在下面的代码实例中会有体现。

代码实例

```python 
import cv2#导入包
import numpy as np
import matplotlib.pyplot as plt
img_test3 = cv2.imread("test3.png")#读入图像
cv2.imshow("test3",img_test3)#展示图片
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
kernel = np.ones((3,3),np.uint8)#设定处理的内核
erosion = cv2.erode(img_test3,kernel,iterations = 1)#腐蚀操作
cv2.imshow("erosion",erosion)#展示图片
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
pie = cv2.imread("pie.png")
cv2.imshow("pie",pie)
cv2.waitKey(0)
cv2.destroyAllWindows()
kernel = np.ones((30,30),np.uint8)#设定要处理的内核大小
erosion_1 = cv2.erode(pie,kernel,iterations = 1)#循环腐蚀1次
erosion_2 = cv2.erode(pie,kernel,iterations = 2)#循环腐蚀2次
erosion_3 = cv2.erode(pie,kernel,iterations = 3)#循环腐蚀3次
All = np.hstack((erosion_1,erosion_2,erosion_3))#拼接图像
cv2.imshow("All",All)
cv2.waitKey(0)
cv2.destroyAllWindows()
img_test3 = cv2.imread("test3.png")
cv2.imshow("test3",img_test3)
cv2.waitKey(0)
cv2.destroyAllWindows()
kernel = np.ones((3,3),np.uint8)#设定要处理的内核大小
erosion_test3 = cv2.erode(img_test3,kernel,iterations = 1)#腐蚀图像
cv2.imshow("erosion_test3",erosion_test3)#展示腐蚀后的图像
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
dilate_test3 = cv2.dilate(erosion_test3,kernel,iterations = 1)#对腐蚀过的图像进行膨胀处理
cv2.imshow("dilate",dilate_test3)#展示膨胀后的图像
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
kernel = np.ones((30,30),np.uint8)#设定要处理的内核大小
dilate_1 = cv2.dilate(pie,kernel,iterations = 1)#循环膨胀一次后的图像
dilate_2 = cv2.dilate(pie,kernel,iterations = 2)#循环膨胀两次后的图像
dilate_3 = cv2.dilate(pie,kernel,iterations = 3)#循环膨胀三次后的图像
All = np.hstack((dilate_1,dilate_2,dilate_3))#拼接以上三幅图像
cv2.imshow("All",All)#展示图片
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
```

​		运行结果

​		这是原图，可以看到上面有一些多出来的粘连部分

![img](https://img-blog.csdnimg.cn/1537e068577245a385599db42e8d174d.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		进行腐蚀操作后的图像，可以看到，我们用腐蚀操作成功去除了边缘的粘连部分，但同时字体笔画也由于受到了腐蚀而变细了

![img](https://img-blog.csdnimg.cn/820a1af369304a0e9db8f8f53781927d.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		对上图进行膨胀操作，可以看到，我们恢复了被腐蚀前笔画的粗细，同时也去除掉了原图的粘连部分，这种操作称为开运算，能够在尽量不改变原图的情况下去除图像的粘连。（在下面会有详细的介绍）

![img](https://img-blog.csdnimg.cn/ffa99cfcef654447a6aedb85382a1394.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)



 		以下是循环腐蚀1~3次之后的图像对比

![img](https://img-blog.csdnimg.cn/db9c35ee294c40378a7e08838d7deb0e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

 		以下是循环膨胀1~3次之后的图像对比

![img](https://img-blog.csdnimg.cn/db9c35ee294c40378a7e08838d7deb0e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		通过上面两幅图可以看出，不管是腐蚀还是膨胀，都不是等比例的进行，它们最终都会趋近于矩形（因为卷积核就是矩形的），并且进行腐蚀再膨胀后的图像跟原图是存在细微差别的，比如中间的部分空洞可能已经消失了等等。

​		开运算和闭运算 

​		所谓开运算在上面的代码其实已经使用过了，只是opencv本身便带有可以进行腐蚀后再膨胀的函数，不需要我们自己写那么多代码。开运算在原图的基础上就是用于消除图像的一些粘连部分的一种方式。

​		而闭运算则相反，是先进行膨胀，再进行腐蚀的一种操作。它主要用于填充图像中的空洞部分，在opencv中同样有一个专门的函数进行闭运算。

​		函数介绍

```python
opening = cv2.morphologyEx(img_test3,cv2.MORPH_OPEN,kernel)
#开运算，img_test3是要进行处理的图片，cv2.MORPH_OPEN表示要进行的是开运算（先腐蚀后膨胀），kernel则跟上面的函数一样，是定义好的卷积核。
```

```python
 closing = cv2.morphologyEx(img_test3,cv2.MORPH_CLOSE,kernel)
#闭运算，这里的函数参数跟上一个函数作用一样，cv2.MORPH_OPEN表示要进行的是闭运算（先膨胀后腐蚀）。
```

代码实例

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
img_test3 = cv2.imread("test3.png")#读入图像
cv2.imshow("test3",img_test3)#展示图片
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
kernel = np.ones((3,3),np.uint8)#设定要处理的内核大小
opening = cv2.morphologyEx(img_test3,cv2.MORPH_OPEN,kernel)#开运算，先腐蚀后膨胀，能够去除图像中粘连的部分
cv2.imshow("open",opening)
cv2.waitKey(0)
cv2.destroyAllWindows()
kernel = np.ones((3,3),np.uint8)#设定要处理的卷积核大小
closing = cv2.morphologyEx(img_test3,cv2.MORPH_CLOSE,kernel)#闭运算，先膨胀后腐蚀，能够填补图像中间的空隙
cv2.imshow("close",closing)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

运行结果

​		开运算:

![img](https://img-blog.csdnimg.cn/8a8d5e9fde0440a89485713f89a2ee34.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		闭运算：效果不明显，但是如果该图像中间有空洞存在，那么我们可以明显的看到空洞被填上了。

 ![img](https://img-blog.csdnimg.cn/dd87b8e084104331a689c3155420fa03.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)



 		梯度运算

​		原理：将图像分别进行膨胀和腐蚀，然后两者相减，则可以得到该图像的轮廓，而opencv中同样提供了进行梯度运算的函数。

​		函数介绍

```python
gradient = cv2.morphologyEx(pie,cv2.MORPH_GRADIENT,kernel)
#这里的pie是将要进行处理的二值图像，cv2.MORPH_GRADIENT表示进行梯度运算，kernel则是定义好的卷积核。
```

​		代码示例

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
pie = cv2.imread("pie.png")
cv2.imshow("pie",pie)#展示原图
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
#梯度运算，通过膨胀减去腐蚀得到轮廓
kernel = np.ones((3,3),np.uint8)#设定卷积核大小
gradient = cv2.morphologyEx(pie,cv2.MORPH_GRADIENT,kernel)#梯度运算
cv2.imshow("gradient",gradient)#展示处理后的图像
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
```

​		运行结果

​		原图

![img](https://img-blog.csdnimg.cn/79e04475f1334a4ca7d3ee22dd7f2ac2.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)



​		处理后得到的图像轮廓

![img](https://img-blog.csdnimg.cn/5e97fdf19d5d4cb1b00e2e4f5e5895b6.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)



 		礼帽与黑帽

​		礼帽：将图像先进行开运算，再以原始图像减去开运算的结果，我们就可以得到图像被腐蚀掉的粘连部分，或者说原图中灰度较亮的区域，所以也称白顶帽变换。

​		黑帽：将图像先进行闭运算，再将闭运算的结果减去原始图像，作用我们就可以得到原图像中被填充的空洞部分，也就是图像中件较暗的空洞区域，所以又称黑底帽变换。

​		函数介绍

```python
tophat = cv2.morphologyEx(img_test3,cv2.MORPH_TOPHAT,kernel)
#礼帽运算，cv2.MORPH_TOPHAT表示进行的是礼帽运算，即原图像-开运算。
```

```python
blackhat = cv2.morphologyEx(img_test3,cv2.MORPH_BLACKHAT,kernel)
#黑帽运算，cv2.MORPH_BLACKHAT表示进行的是黑帽运算，即闭运算-原图像。
```

​		代码示例

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
img_test3 = cv2.imread("test3.png")#读入图像
cv2.imshow("test3",img_test3)#展示图片
cv2.waitKey(0)
cv2.destroyAllWindows()#关闭窗口
#礼帽，原始图像-开运算，得到的就是被腐蚀掉的粘连部分
kernel = np.ones((3,3),np.uint8)#设定卷积核大小
tophat = cv2.morphologyEx(img_test3,cv2.MORPH_TOPHAT,kernel)#礼帽运算
cv2.imshow("tophat",tophat)
cv2.waitKey(0)
cv2.destroyAllWindows()
#黑帽运算，闭运算-原始图像，得到的是膨胀之前原始图像中比较暗的部分，即中间的空洞
kernel = np.ones((7,7),np.uint8)#设定卷积核大小
blackhat = cv2.morphologyEx(img_test3,cv2.MORPH_BLACKHAT,kernel)#黑帽运算
cv2.imshow("blackhat",blackhat)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

​		运行结果

​		原图

![img](https://img-blog.csdnimg.cn/fde8971efb624edaae8249e9fd99135d.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		礼帽，可以看到图像粘连部分被剔除出来了

![img](https://img-blog.csdnimg.cn/172685db4ddf4cc5a03a795d511eaa8f.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)

​		黑帽，我们得到了迪哥中间微小的空洞部分

![img](https://img-blog.csdnimg.cn/03c150953443454a9facecb8d317ef70.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5b-1OTgw,size_20,color_FFFFFF,t_70,g_se,x_16)