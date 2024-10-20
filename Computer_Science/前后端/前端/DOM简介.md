## DOM简介

#### 2.1 为什么需要DOM

  前边我们所学习的JS基础课程，学习了JS的基础知识。但是在学习过程中你会发现，似乎JS和网页并没有太大的关系。换句话说，我们所编写的代码，除了是写在网页中以外，**并没有和网页产生任何实质的联系**。**如果JS不能操作网页，那么对于我们来说它就是一个废物**，没有任何的使用价值。**所以我们就需要一个新的技术，一个可以让我们使用J来操作网页的技术，也就是DOM.**

#### 2.2 什么是DOM

  **DOM，全称Document Object Model，中文翻译为文档对象模型。** DOM属于**Web API**的一部分。Web API中定义了非常多的对象，**通过这些对象可以完成对网页的各种操作(添加删除元素、发送请求、操作浏览器等)**

  ① DOM中的D意为Document，即文档。所谓文档就是指整个网页，换言之，DOM是用来操作网页的。
  ② O意为Object，即对象。**DOM将网页中的每一部分内容都转换为了对象，div有div的对象，input有input的对象，甚至一段文本，一段注释也有其所对应的对象。** 转换为对象干什么?还记得面向对象吗?转换对象以后，我们就可以**以面向对象的方式去操作网页，想要操作哪个元素就获取哪个元素的对象，然后通过调用其方法或属性完成各种操作。**
  ③ M意为Model，即模型模型用来表示对象之间的关系，也就是父子元素、祖先后代、兄弟元素等，明确关系后我们便**可以通过任意一个对象去获取其他的对象。**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3bc88f905b994e29ab2ad6deeca298c7.png)

#### 2.3 节点与关系

  

![### 2.2 什么是DOM](https://i-blog.csdnimg.cn/direct/c439df6836614308989af8af7e6b05d6.png)
  

## 三、如何使用DOM🚀🚀🚀

#### 3.1 入门案例

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c183187b769346acb7ace2a043a81f9d.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2b0a12d3c80344299b2514a4e9e1663c.png)

  通过JS代码可以获得按钮的对象，那么就可以通过JS来修改按钮的属性（文字、颜色、大小等）

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/907f53bd588e4f1bb323d742ec0d363f.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ec1a06069fb349889004028eb2efde84.png)

  

#### 3.2 文档结点 | Doucument对象（代表整个网页）

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/db4cc29a0a624a83869887bcacb1033e.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e8dcea14c6d64f86941992c2f782cec6.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d97f70d9991f461d8ccd6c10b7cc52f4.png)

#### 3.3 元素节点（代表每一个标签）

#### ① 如何获取元素节点

  **doucument是代表整个网页，而元素节点element就代表某个标签。**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9fdd9593cd7b40bda580ae9279b0c2b6.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c76425d63237467d92babc597bb0aecc.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3167f16adcab444980461eba92475b1a.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/997cae0ed9de43b880f5625f27ba2d38.png)

**除了这些，还有两个更强大的方法：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c6b04bf1dd794f419ed4e43da6962174.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/27de45f73d6049a0b16e078ba3db258c.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1c8bed1c419d4b8985de2b52038991ca.png)

#### ② 元素节点（方法小总结）

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/572ef6968f9d4dfeabb3372eccda122b.png)

#### ③ 元素节点的属性和方法

  上面我们讲的是如何去获取元素节点 ，接下来我们看一下元素节点的结构，也就是它的这个**原型链**，
我们先简单的写一段js代码通过元素ID获取标签对象。如下图：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cccc7a6c47ce40e2a085ee86720ce92b.png)

我们可以直接看到如下：直接把这个东西给打印出来了。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/57696b5097ba4c148f3757b64b083da7.png)

现在的话我们来看一下它的原型链。（我们这里看的是div它的原型链）

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3179dbb350d846199e39703c62d1be9b.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1e161d9684744570b611bb11d0957797.png)

如果是其他标签，比如span，那它的HTMLDivElement这个元素会变。

  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b637b9c304b246a0814e54b5b6fdcfcc.png)

  

**这里还有几个注意的方法。** 第二个方法比较实用一点。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cf0baccdce274c7084d06c7c7000d8d8.png)

#### 3.4 文本节点

  前面教的内容是不是可以通过元素去获得文本节点对象，但是我们一般不会这么做，在DOM中网页的所有内容都是文本对象。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d28e7af247c643ab874b0090e05e4597.png)

  
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3f24dc675a4d467080e39f33580f99b9.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2e4519147c5d445792345119bd905f04.png)

  即上面这个并不能作为正在的标签去显示。

**重点：xss注入与element.innerHTML**

  什么叫xss注入呢，就是一些别有用心的人把游戏恶意的代码注入到我们的网站当中去，注入以后可能会窃取到网页中用户的信息等。
如下图：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/998d70bf1c2f4c1d829fc14574b59ae5.png)

假设你这一块是一段留言，他以留言的方式给你插入了这一行代码，那注意了， 这行代码他能看见，其他人访问你的网站的话，也会使得这个脚本在其他人的网站上运行。

**小总结**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d59952c093f0472cb82562f739353da9.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e6b032b21c9e4540ad8e24b84b88a3dc.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fd1f90d47c5d4126a61c21a92c0f4c8d.png)![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4c5b5ea57cf347bba21e37642a0a0734.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/28262ffbe8794d54b94ca5ee1331ca59.png)

  

#### 3.5 属性节点

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3a0e234132d04260880e28d98a074a2a.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2700bac368454184a08b29926f3b6b35.png)

## 四、DOM相关概念/知识🚀🚀🚀

#### 4.1 事件

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/27801873a79540efad006e3151f107d4.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4989b37e7efc4d6082f0efa0fe9b2c51.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/61f3d1aa94844d75802a6fd46de93571.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ee9c78a3f7814062a65bee591cf31776.png)

  
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d763173a225f4fd48367ef947b73ad2b.png)

  

#### 4.2 文档的加载

  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/63e442818121437a8ae0d2320d5cceaf.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/23eaba62bad1492f83b5b098331cff86.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bbc92fde15fb4c949eb3c135fa3f62b4.png)

  这是什么原因，const btn = document.getElementById（“btn”）,这句话是**当浏览器把网页给加载完后，它会自动根据网页当中的元素去生成对象**。加载网页就生成一个document对象，加载html就生成一个html元素对象。加载到哪就生成什么对象。
  那当我们把代码写在上面的时候，是不是**谁先加载谁就先执行了**，写在上面先执行了，下面这一堆还没有加载，那这个btn还没有所以就获取不到。

**这里有四种实现方法**
（注意：回调函数会在我们的窗口加载完了以后才执行）

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1e70ade3bfb441d285f75bddefb11fe8.png)

**总结**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2bc54017ca52405c8446f852d8fa63bd.png)

  

#### 4.3 练习

##### ① 图片按钮点击切换

**需求：** 我们有几张图片，然后在网页当中把图片给显示出来，然后整两个按钮，通过按钮的点击来切换这个图片。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/279d248bfb414656a323b4ef34b1570e.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3f65a41e5dcd421bab6eef7d832e18b3.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ce1659c4cfba44979d5092c37334c244.png)

  这里相当于把切换图片给写死了，因为只能转上下张，并且这里图片名称要为1和2。缺乏灵活性。要是路径是英文该怎么办勒？

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/11f94714666d4afc979a4a69a819a505.png)

  但是这边它的索引页写死了，我们需要动态的变换。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/003732be56c746ffbae5f7ed6d43dab2.png)

这里由于current不能小于0与大于图片的总数量，所以可以在逻辑上加一点校验。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/40e433b22ae645a29a0f35cbe1e3708c.png)

如何实现？

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/428aaa899a974c5da912b466ed7e33cc.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/780402ea70174a6daeee583784283604.png)

  

##### ② 按钮点击全选

  

**body内容：**
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/491d7f8d085f4fc8b2a4890673205f3e.png)

**全选按钮：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/357e0734919c4cf88bcf25b41cee3fd4.png)

**获取取消按钮和反选功能：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/51cbcfbef4d24ccb9b6ce0cc1d89862e.png)

  
查看

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/68149a6afea74c1c9416216b194c1dcb.png)
  
**点击全选checkbox，小的checkbox和它同步**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/526da62fdd204d649828822d6a81bc6d.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e82939fcf9e943e3b7eafea7e635e763.png)

到这里代码功能就全部实现了，但是可以看到代码比较冗杂，复用性不高。

  

#### 4.4 元素的增删改

  **元素的修改**

**body部分：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9710052a15704ccb916e50f607031d44.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/09f3253b2c424222923b3ace57c28aeb.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/920bc84c6bd8443296d1e1547af44e10.png)

------

  完善后整体的代码：

**body内容：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8b4c5c7cc7f64be483cc8d7dce250459.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8e2f94f07f294ba4ac713e49daf18809.png)

**script内容：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a346a6d53a984dbfa46c20050836a012.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/99f3b957705249b89f82c2035c6b52c9.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f2d339cbbb3f45c7ab91746dbe5a2bad.png)![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/87a14a45807a47aba3a04a134b634683.png)

#### 4.5 如何解决XXS注入问题

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e7c4e4be05ec45b09535ea5cf41e7779.png)

#### 4.6 节点的复制

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/321d3c2773fe439c9154453376944761.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5b318394daf04e9e8c09f916a6095d2b.png)

## 五、JS操作CSS🚀🚀🚀

  前面我们学的可以说是js如何操作结构，然后接下来将学习操作css。

#### 5.1 修改CSS样式

  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/57df8533304b41c5808a2d5477a39b6d.png)
  

#### 5.2 读取CSS样式

  **getComputedStyle()，它会返回一个对象，这个对象中包含了当前元素所有的生效的样式**
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b789646d35e14efebfe475a143d4339e.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1e9d333251934fc7b146789baa5fa22f.png)

  

#### 5.3 通过属性读取CSS样式

  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/31f0e4ae19df4d089b4c51dbffcea965.png)

**body部分：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b69dc5b9a53c40f5a48390511028be0a.png)

**script部分：**

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e61b57a6c48b492893443ca62c614c2c.png)![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/987b0ed7ad1942a290ba0948dcd7cfde.png)
  

#### 5.3 操作class修改样式

  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/08ed05923fcc471e81bb0195ed662df9.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ddb7056927b44cac92a1175d1d522644.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e983aa183cb6457dacf49edaf6c44849.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/34596d78fbf847708081e715434436fc.png)

## 六、事件对象🚀🚀🚀

#### 6.1 事件对象简介

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1398d80216f34072bb6b1d972a2bed23.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/117664b8b1624d459d28b53f2ed7f07d.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/090bdd8a61fb4b74be15e9a470506dcc.png)

  

#### 6.2 Event对象

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/27588d5687414c1fa84cd486a7902b5b.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7ebac3048d8648358916c5e6c16217d8.png)

#### 6.3 事件的冒泡

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ab118369af934dce98ad08dd5795fc0c.png)

#### 6.3 事件委派

  我们本来是要一个一个绑定事件的，但是可以直接通过委派把事件绑定给doucument，完了后事件我们只需要绑定一次，即可让多个元素拥有该事件。统一把事件委托给doucument管了。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/306eefde25d840d1b554eaa1191ac0dc.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c82dd4e441cf4c018714d2bbef15fd51.png)

#### 6.4 事件的捕获

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/485f6781fba340529648a83f4d514152.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c02fd3f5f09b46289a52362731ee42f1.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/87525ee9006a4452be3de1f06b86424b.png)

  
  

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3191160b7e974aeab665df072f0ee753.png)

  