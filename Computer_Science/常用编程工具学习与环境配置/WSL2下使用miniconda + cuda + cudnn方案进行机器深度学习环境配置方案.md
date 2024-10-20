# WSL2下使用miniconda + cuda + cudnn方案进行机器/深度学习环境配置方案

## 前言

​	笔者这几天需要使用Google的mediapipe框架进行自定义的数据训练，值得注意到的是Google家的这个方便的自定义训练只支持在Linux下完成。具体原因可以参考到

> [tty — Terminal control functions — Python 3.13.0 documentation](https://docs.python.org/3/library/tty.html)

​	也即是google.colab库需要的环境就是Unix系的OS。。。所以没办法（耸肩），只好在WSL上完成mediapipe应用框架的搭建，刚好笔者准备尝鲜。

## 方案简单前置

1. 笔者认为您的电脑已经安装好了WSL2且使用的是默认的发行版（Ubuntu）

   ```
   ➜  wsl --list
   适用于 Linux 的 Windows 子系统分发:
   Ubuntu-24.04 (默认)
   ```

   您可以参考任何一篇安装WSL2的教程，笔者认为官方的最为权威：

   > https://learn.microsoft.com/zh-cn/windows/wsl/install

2. 笔者认为您的电脑上有可以使用的GPU用于深度学习模型的训练。

   > 笔者自己就在windows上有nvcc等工具链，因此直接梭哈，当然没有也没关系，我们后面安装的是WSL的驱动

   ```
   ➜  nvcc --version
   nvcc: NVIDIA (R) Cuda compiler driver
   Copyright (c) 2005-2024 NVIDIA Corporation
   Built on Fri_Jun_14_16:44:19_Pacific_Daylight_Time_2024
   Cuda compilation tools, release 12.6, V12.6.20
   Build cuda_12.6.r12.6/compiler.34431801_0
   ```

3. 笔者认为您的电脑已经安装好了vscode。且安装好了python插件用于辅助我们在VSCode上书写Python程序

## 方案配置说明

​	最终，你的WSL2的目标发行版上将会有一个可以使用Host OS上正在使用的GPU训练深度模型的一个深度学习框架。

## Step 1: 安装Miniconda

>[Miniconda — Anaconda documentation](https://docs.anaconda.com/miniconda/)

​	这是Miniconda的官方网站，下载这个的原因十分简单：它简单轻量。

> 有代理的朋友直接使用wget梭哈脚本就行了
>
> 没有代理的朋友使用清华源下载：
>
> ```
> wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh
> ```
>
> 特定版本的前往：[Index of /anaconda/miniconda/ | 清华大学开源软件镜像站 | Tsinghua Open Source Mirror](https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/?C=N&O=D)慢慢搜索

​	使用wget下好脚本之后，我们就可以梭哈了。

```
bash Miniconda3-latest-Linux-x86_64.sh
```

​	一路摁enter（默认的，我懒）

## STEP 2: 创建一个环境

​	但是你会发现：你没有办法使用conda，因为你的bash没有检索到它！

```
export PATH=$PATH:/home/charliechen/miniconda3/bin
```

​	笔者的偷懒办法是在自己的bashrc上添加一行这个，让我们的环境变量找到我们的conda可执行文件就OK！

```
➜  conda --help
usage: conda [-h] [-v] [--no-plugins] [-V] COMMAND ...

conda is a tool for managing and deploying applications, environments and packages.
...
```

​	现在输出就是正确的了。

​	下面我们创建一个环境，使用conda创建环境很简单：

```
conda -n env_name(不要照抄！自己设置一个有意义的名字) python=python_version
```

​	举个例子，笔者的创建是：

```
conda -n Ican_Model_Train python=3.8
```

​	现在，使用

```
conda activate Ican_Model_Train
```

​	激活我们刚刚创建的环境，这个时候你会发现你的shell多了（Ican_Model_Train），那就是成功了。

## STEP 3: VSCode链接WSL虚拟机

​	这个事情参考WSL如何链接虚拟机：[Get started using VS Code with WSL | Microsoft Learn](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode)

## STEP 4：安装WSL的nvidia tool kit

​	欸！先别急着apt install，不是这样玩的：

> [CUDA on WSL (nvidia.com)](https://docs.nvidia.com/cuda/wsl-user-guide/index.html#getting-started-with-cuda-on-wsl-2)

​	参考官网的教程，人家叫你使用手动安装的方式，WSL现在可以直通GPU了。所以不要使用旧的方案！！！**不要使用旧的方案！！！**

​	办法是：[CUDA Toolkit 12.6 Update 2 Downloads | NVIDIA Developer](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=WSL-Ubuntu&target_version=2.0)

```
wget https://developer.download.nvidia.com/compute/cuda/repos/wsl-ubuntu/x86_64/cuda-wsl-ubuntu.pin
sudo mv cuda-wsl-ubuntu.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/12.6.2/local_installers/cuda-repo-wsl-ubuntu-12-6-local_12.6.2-1_amd64.deb
sudo dpkg -i cuda-repo-wsl-ubuntu-12-6-local_12.6.2-1_amd64.deb
sudo cp /var/cuda-repo-wsl-ubuntu-12-6-local/cuda-*-keyring.gpg /usr/share/keyrings/
sudo apt-get update
sudo apt-get -y install cuda-toolkit-12-6
```

​	笔者列出来当时Nvidia官方给予我的方案。如上所示，照做即可。看官可以自行进入上述网址完成自己的方案配置。

​	检查我们的安装是否正常：

```
➜  nvidia-smi # 这个是Windows上如果就有就会带，没有请安装Windows的nvidia-smi程序！在Windows上的！！！
Thu Oct 10 23:16:41 2024
+-----------------------------------------------------------------------------------------+
| NVIDIA-SMI 560.28.03              Driver Version: 560.76         CUDA Version: 12.6     |
|-----------------------------------------+------------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
|                                         |                        |               MIG M. |
|=========================================+========================+======================|
|   0  NVIDIA GeForce RTX 3060 ...    On  |   00000000:01:00.0  On |                  N/A |
| N/A   39C    P8             14W /   95W |    1450MiB /   6144MiB |      3%      Default |
|                                         |                        |                  N/A |
+-----------------------------------------+------------------------+----------------------+

+-----------------------------------------------------------------------------------------+
| Processes:                                                                              |
|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |
|        ID   ID                                                               Usage      |
|=========================================================================================|
|    0   N/A  N/A        25      G   /Xwayland                                   N/A      |
+-----------------------------------------------------------------------------------------+
```

```
➜  nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2024 NVIDIA Corporation
Built on Thu_Sep_12_02:18:05_PDT_2024
Cuda compilation tools, release 12.6, V12.6.77
Build cuda_12.6.r12.6/compiler.34841621_0
```

​	如果你的nvcc --version找不到，不要气馁：

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib
export PATH=$PATH:/usr/local/cuda/bin
```

​	现在试试看！成功的话可以考虑写入bashrc文件！

## STEP 5：安装上层框架

​	笔者玩的是Google MediaPipe，所以只需要一行话就可以把所有的上层框架装好就行！当然，如果是tensorflow，那就需要安装如下的python接口库：

```
conda install -c conda-forge cudatoolkit=11.8.0
pip install nvidia-cudnn-cu11==8.6.0.163
```

​	版本可以自行调整，建议如果常常使用GPU，将加载写入conda目标虚拟环境的加载脚本中

```
mkdir -p $CONDA_PREFIX/etc/conda/activate.d
#如果跳过了第三节，则即使用sudo下面的命令也会报权限错误，需要在~/miniconda3/etc/conda/activate.d目录下新建env_vars.sh文件，将单引号中的内容复制到文件中
echo 'CUDNN_PATH=$(dirname $(python -c "import nvidia.cudnn;print(nvidia.cudnn.__file__)"))' >> $CONDA_PREFIX/etc/conda/activate.d/env_vars.sh
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CONDA_PREFIX/lib/:$CUDNN_PATH/lib' >> $CONDA_PREFIX/etc/conda/activate.d/env_vars.sh
```

​	现在我们的动态依赖库安装好了

​	下面就是安装torch或者是tensorflow了

### [Optional if target is torch]安装torch

​	查看[PyTorch](https://pytorch.org/)的解决方案就行

### [Optional if using Tensorflow]安装tensourflow

```
pip install tensorflow
```

### 笔者玩的mediapipe

```
pip install mediapipe-model-maker
```

## STEP 6：测试

### Tensorflow系列

​	mediapipe底下使用的是tensorflow，因此这里可以合并检测tensorflow的使用

```
➜  head model_train.py -n 30
# from google.colab import files
import os
import tensorrt as trt
import tensorflow as tf
assert tf.__version__.startswith('2')
print(tf.__version__)
from mediapipe_model_maker import gesture_recognizer

import tensorflow as tf
print(tf.test.is_gpu_available())	# True

print(tf.config.list_physical_devices('GPU'))	# 你的GPU列表
```

### Torch系列

```
torch.cuda.is_available()
```

> 若返回为True，则使用的是GPU版本的torch，若为False，则为CPU版本

```
print(torch.cuda.get_device_name(0))
```

​	返回的GPU型号为你使用的GPU型号

## STEP 7:开始愉悦炼丹！