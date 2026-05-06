<img width="1643" height="604" alt="image" src="https://github.com/user-attachments/assets/da5f9e23-527b-417d-8847-b3bdd60fed6a" />

<img width="160" height="160" alt="image" src="https://github.com/user-attachments/assets/aefe2bdf-73c9-4f30-82d7-85d8a896bc51" />


# 一、材料准备

为了使用方便以及技术能力限制，该教程仅适用于双显卡计算机（单显卡理论上可行但不适用于本教程）。你需要拥有一个主要显卡用于提供给Windows虚拟机，以及副显卡用于显示Ubuntu的图形化界面，推荐使用 独显+核显 的方式，或者使用 独显+亮机卡（需要主板支持）。

下面是需要事先准备的材料：

1.需要32GB及以上的U盘

2.双显卡计算机

3.两个及以上的显示屏

4.两副及以上的鼠标键盘

5.至少一个耳机或外放设备



计算机配置参考：

① 台式配置参考

主板：铭瑄 H610M

CPU：i3-12100（核显）

显卡：铭瑄 GTX1660S

内存条：光威 DDR4 16 * 2 3200

硬盘：M2 SSD 2TB

②笔记本配置参考

惠普 暗影精灵9

CPU：i9-13900HX

显卡：RTX 4060 mq

内存：DDR5 8G * 2

硬盘：M2 SSD 2TB

请尽量选择默频较高并且全大核的CPU，这里推荐以AMD的CPU为主，但是该方法未经过测试，仅供参考



#### 参考教程：[【Ubuntu安装详细教程】](https://www.bilibili.com/video/BV1CG4y1h7bx/?share_source=copy_web&vd_source=5dd9f751a12a9cae6d790540acdc6fb0) 



# 二、制作启动盘

使用Ventory制作启动盘：

下载地址参考：[https://www.ventoy.net/cn/download.html](https://www.ventoy.net/cn/download.html)

下载完Ventory以后根据[官网教程](https://www.ventoy.net/cn/doc_start.html)制作启动盘，注意U盘内如果有重要文件需要提前备份，制作启动盘时会对U盘进行格式化。

下载Windows 10 22H2 ISO 镜像

[Win10镜像下载链接](https://www.microsoft.com/zh-cn/software-download/windows10)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 1.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 2.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 3.png)

将windows镜像保存到你的硬盘上，随后复制进你刚做的U盘启动盘或者是其他可移动存储器上

下载Ubuntu 24.04 LTS 镜像

[Ubuntu下载链接](https://cn.ubuntu.com/download/server/step1)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 4.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 5.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 6.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 7.png)

将下载好的镜像保存到你刚做好的启动盘中



# 三、硬盘预留空间

如果你专门为Ubuntu系统预留了一块硬盘，并仅在该硬盘上使用Ubuntu系统，你可以跳过这个步骤

建议使用你的系统硬盘，或者选择可靠的M2槽以及SSD作为Ubuntu的系统盘。

打开计算机管理（对桌面上的此电脑右键管理）

找到磁盘管理，如图所示

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 8.png)

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 9.png)

此处我选择C盘作为Ubuntu系统盘，右键C盘，选择压缩卷。

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 10.png)

选择需要压缩的大小，建议至少256GB，及262144MB。

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 11.png)

如图所示，需要留下足够的未分配空间，建议在256G及以上



# 四、安装Ubuntu系统

因为手头上不方便使用其他电脑，以下以技嘉主板B250M主板作为例子

将电脑关机，插上制作好的启动盘

![IMG_20250429_09455901.jpg](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/IMG_20250429_09455901.jpg)

开机，进入BIOS启动项选择。铭瑄为F11，技嘉及多数主板为F12，根据主板型号自行查询

↑ 在BIOS中选择Ventory或UEFI USB U盘启动

![IMG_20250429_09462001.jpg](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/IMG_20250429_09462001.jpg)

↑ 选择Try or Install Ubuntu

![Screenshot+from+2025-04-29+01-54-58.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-54-58.png)

↑ 进入Ubuntu安装界面

![Screenshot+from+2025-04-29+01-55-46.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-55-46.png)

↑ 选择简体中文

![Screenshot+from+2025-04-29+01-56-13.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-56-13.png)

↑ 下一步

![Screenshot+from+2025-04-29+01-56-23.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-56-23.png)

↑ 键盘布局汉语，也可以选择英语

![Screenshot+from+2025-04-29+01-57-00.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-00.png)

↑ 连接网络（可选）

![Screenshot+from+2025-04-29+01-57-13.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-13.png)

↑ 现在更新（可选），但是会降低安装速度，此处选择跳过

![Screenshot+from+2025-04-29+01-57-23.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-23.png)

↑ 选择安装Ubuntu

![Screenshot+from+2025-04-29+01-57-32.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-32.png)

↑ 选择交互安装

![Screenshot+from+2025-04-29+01-57-45.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-45.png)

↑ 选择扩展集合

![Screenshot+from+2025-04-29+01-57-57.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-57-57.png)

↑ 安装推荐的专有软件 全部勾选

![Screenshot+from+2025-04-29+01-58-10.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-58-10.png)

↑ 安装类型请注意，如果你的硬盘中还有其他需要的资料或系统，请选择“手动分区”。如果该硬盘你只为装ubuntu而用，你可以选择清除整个磁盘。

以下以选择“手动分区”为例

![Screenshot+from+2025-04-29+01-58-46.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-58-46.png)

↑ 根据之前压缩硬盘的空间找到剩余空间，这里我在Windows中压缩的是186G

![Screenshot+from+2025-04-29+01-59-05.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-59-05.png)

↑ 挂载点选择  / 

![Screenshot+from+2025-04-29+01-59-16.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-59-16.png)

↑ 默认自动选择刚创建的空盘，点击下一步

![Screenshot+from+2025-04-29+01-59-40.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-59-40.png)

↑ 设置你的用户名和密码

![Screenshot+from+2025-04-29+01-59-46.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+01-59-46.png)

↑ 时区默认上海（别问，没有北京时间）

![Screenshot+from+2025-04-29+09-59-57.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+09-59-57.png)

↑ 点击安装

![Screenshot+from+2025-04-29+10-01-19.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+10-01-19.png)

↑ 开始安装系统

![Screenshot+from+2025-04-29+10-20-51.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Screenshot+from+2025-04-29+10-20-51.png)

↑ 安装完以后会提示需要重启，点击重启

![IMG_20250429_10214101.jpg](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/IMG_20250429_10214101.jpg)

↑ 重启时会用英文提示需要拔掉启动盘，这个时候请直接拔掉U盘，之后再按下回车

可能会进入Ubuntu的引导页面，选择Ubuntu即可，或者等待倒计时结束默认选择

![截图+2025-04-29+10-22-42.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/截图+2025-04-29+10-22-42.png)

↑ 完成Ubuntu系统安装

双系统用户可以在BIOS中可以选择默认启动的系统，可以按照主板的型号查询具体的步骤，根据需要选择开机启动哪一个系统，临时切换可以和选择启动盘一样按F12选择自己需要启动的系统。



#### 安装后的杂项修改(整活可选)

**修改默认启动项为windows**

- vim /etc/default/grub

    GRUB_DEFAULT=4 //修改本行数字为选择ubuntu后启动页面windowsboot在第几行，这样可以设置windows为启动默认选择项，注意从0开始数

    update-grub     //保存退出后更新策略



# 五、环境搭建

#### BIOS设置更改：

使用虚拟机需要在BIOS中开启CPU虚拟化，一般叫做VT-x、VT-d（对于Intel处理器）或AMD-V、AMD-Vi（对于AMD处理器），启用Intel (VMX) Virtualization Technology或者SVM

启动系统

在命令行中输入以下命令

```Plain Text
# 更新软件包列表
sudo apt-get update

# 安装硬件虚拟化检测工具，用于检查CPU是否支持KVM虚拟化。
sudo apt-get install -y cpu-checker

# 安装KVM/QEMU虚拟化工具与图形化管理界面
sudo apt-get install -y qemu-kvm virt-manager libvirt-daemon-system virtinst libvirt-clients bridge-utils

# 图形与视频驱动
sudo apt-get install -y va-driver-all vdpau-driver-all
sudo apt-get install -y intel-media-va-driver-non-free
sudo apt-get install -y libegl1-mesa-dev libgl1-mesa-dev libopus-dev libqt5svg5-dev libsdl2-dev libsdl2-ttf-dev libssl-dev libavcodec-dev libva-dev libvdpau-dev libxkbcommon-dev qtwayland5 qt5-qmake qtbase5-dev qtdeclarative5-dev qtquickcontrols2-5-dev wayland-protocols qml-module-qtquick-controls2 qml-module-qtquick-layouts qml-module-qtquick-window2 qml-module-qtquick2

# 系统工具与内核
sudo apt-get install -y fuse libfuse2
sudo apt-get install -y net-tools
sudo apt-get install -y linux-oem-24.04c

# C++编译及开发工具
sudo apt-get install -y clang-14 make cmake libboost-all-dev libfmt-dev zlib1g-dev libssl-dev build-essential
sudo apt-get install -y gnome-control-center

# 显示协议调整
filename='/etc/gdm3/custom.conf'
sudo sed -i 's/^#WaylandEnable=false/WaylandEnable=false/g' "$filename"
```

重启Ubuntu

禁用Wayland

```Plain Text
sudo apt install -y vim
sudo vim /etc/gdm3/custom.conf
```

取消注释 /etc/gdm3/custom.conf 中的 #WaylandEnable=false

以上操作并非全部必要，但是必须要有C++的编译环境以及KVM/QEMU

此时你应该的电脑上应该有以下软件

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 12.png)



# 六、KVM虚拟机安装

重启Ubuntu

将你准备的Windows 22H2 ISO镜像放在比较方便寻找的目录下

打开 虚拟系统管理器 

![0+7LY+2@82OMTO+$1++Y$12.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/0+7LY+2@82OMTO+$1++Y$12.png)

↑ 文件→新建虚拟机

![I+PF_B++S6+MUURD+4R3G9C.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/I+PF_B++S6+MUURD+4R3G9C.png)

↑ 本地安装介质（ISO镜像）

浏览选择你的ISO文件

如果不能识别则取消勾选自动从安装介质检测，手动选择windows版本

![@EG1WNI+26+F7U07JX+8++E.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/@EG1WNI+26+F7U07JX+8++E.png)

↑ 内存与CPU数分配请根据自己的配置来决定，以下以War Thunder游戏作为例子，建议分配8核16GB起步

![$2+51P+P2I9+N~BG1H21Z3B.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/$2+51P+P2I9+N~BG1H21Z3B.png)

↑ 虚拟机磁盘存储建议在150G及以上

![+AVUS+I8A+$KOIB6LXY`I+L.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/+AVUS+I8A+$KOIB6LXY`I+L.png)

↑ 虚拟机名称请改为 win10 ，不能是其他名称，否则需要去修改源代码

勾选在安装前自定义配置

![52~MU@04+5$I03490XG85+V.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/52~MU@04+5$I03490XG85+V.png)

↑ 概况→固件 选择UEFI引导 应用

![DCXTZY+XJSCP791X@$QEZ+2.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/DCXTZY+XJSCP791X@$QEZ+2.png)

↑ 引导选项 勾选SATA COROM 光盘并移动到第一位

![+B+DE+ZP+++YOP+0TR2W+CA.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/+B+DE+ZP+++YOP+0TR2W+CA.png)

左上角开始安装

安装完以后将刚才的引导选项改动复位，检查虚拟机是否正常，此时虚拟机无显卡



# 七、显卡直通

非常详细的[显卡直通参考教程](https://askubuntu.com/questions/1406888/ubuntu-22-04-gpu-passthrough-qemu)

以下图片为暗影精灵笔记本的显卡直通过程

笔记本请在BIOS设置中关闭独显直连

#### 1.检查CPU的IOMMU支持

    Intel处理器

    ```Plain Text
    cat /proc/cpuinfo | grep --color vmx
    ```

    可以看到如下高亮的VMX标识

    ![V+GAN59C+8X++8+JU+FWJ98.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/V+GAN59C+8X++8+JU+FWJ98.png)

    AMD处理器

    ```Plain Text
    cat /proc/cpuinfo | grep --color svm
    ```

#### 2.启用IOMMU

    ```Plain Text
    sudo nano /etc/default/grub
    ```

    将以下选项添加到 GRUB_CMDLINE_LINUX_DEFAULT=""

    Intel处理器

    ```Plain Text
    intel_iommu=on kvm.ignore_msrs=1
    ```

    AMD处理器

    ```Plain Text
    amd_iommu=on kvm.ignore_msrs=1
    ```

#### 3.更新GRUB

```Plain Text
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

![$3+@5_SIUJ+YNG+PT5V+5S5.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/$3+@5_SIUJ+YNG+PT5V+5S5.png)

#### 4.重启

#### 5.检查IOMMU是否已启用

```Plain Text
sudo dmesg | grep -i -e DMAR -e IOMMU
```

可以看到类似的信息

```Plain Text
[    0.123456] pci 0000:09:00.0: Adding to iommu group 1
[    0.234567] pci 0000:0a:00.0: Adding to iommu group 2
[    0.345678] DMAR: Intel(R) Virtualization Technology for Directed I/O
```

![U59+F3O@TQORGM`+TIV+AMI.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/U59+F3O@TQORGM`+TIV+AMI.png)

#### 6.设备查找

```Plain Text
lspci -nnk
```

可以看到类似的信息

```Plain Text
01:00.0 VGA compatible controller [0300]: NVIDIA Corporation TU117 [GeForce GTX 1650] [10aa:10bb] (rev a1) (prog-if 00 [VGA controller])
    Subsystem: Micro-Star International Co., Ltd. [MSI] TU117 [GeForce GTX 1650] [0101:a1a1]
    Flags: bus master, fast devsel, latency 0, IRQ 151, IOMMU group 1
    Memory at de000000 (32-bit, non-prefetchable) [size=16M]
    Memory at c0000000 (64-bit, prefetchable) [size=256M]
    Memory at d0000000 (64-bit, prefetchable) [size=32M]
    I/O ports at e000 [size=128]
    Expansion ROM at 000c0000 [disabled] [size=128K]
    Capabilities: <access denied>
    Kernel driver in use: nouveau
    Kernel modules: nvidiafb, nouveau

01:00.1 Audio device [0403]: NVIDIA Corporation Device [01cc:01ee] (rev a1)
    Subsystem: Micro-Star International Co., Ltd. [MSI] Device [0202:a2a2]
    Flags: bus master, fast devsel, latency 0, IRQ 17, IOMMU group 1
    Memory at df080000 (32-bit, non-prefetchable) [size=16K]
    Capabilities: <access denied>
    Kernel driver in use: snd_hda_intel
    Kernel modules: snd_hda_intel
```

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 13.png)

记录显卡后面的ID信息，分别为[10aa:10bb]和[01cc:01ee]

如果你看到 “**Kernel driver in use: nvidia**”

```Plain Text
01:00.0 VGA compatible controller [0300]: NVIDIA Corporation TU117 [GeForce GTX 1650] [10aa:10bb] (rev a1)
    Subsystem: Micro-Star International Co., Ltd. [MSI] TU117 [GeForce GTX 1650] [0101:a1a1]
    Kernel driver in use: nvidia
    Kernel modules: nvidiafb, nouveau, nvidia_drm, nvidia
01:00.1 Audio device [0403]: NVIDIA Corporation Device [01cc:01ee] (rev a1)
    Subsystem: Micro-Star International Co., Ltd. [MSI] Device [0202:a2a2]
    Kernel driver in use: snd_hda_intel
    Kernel modules: snd_hda_intel
```

这意味你需要卸载当前所有的NVDIA驱动程序，重新安装nouveau

命令如下：

```Plain Text
sudo nvidia-settings --uninstall
sudo apt-get remove --purge nvidia*
sudo apt-get remove --purge xserver-xorg-video-nouveau
sudo apt-get remove --purge xserver-xorg-video-nv
sudo apt-get install nvidia-common
sudo apt-get install xserver-xorg-video-nouveau
sudo apt-get install xserver-xorg-video-all
sudo apt-get install --reinstall libgl1-mesa-glx libgl1-mesa-dri
sudo apt-get install --reinstall xserver-xorg-core
sudo dpkg-reconfigure xserver-xorg
```

或者使用以下命令

```Plain Text
software-properties-gtk --open-tab=4
```

选择选项 “X.Org X server -- Nouveau display driver from xserver-xorg-video-nouveau (open source)”

运行自动删除

```Plain Text
sudo apt autoremove
```

重启系统，重复这些步骤直到成功

![2SW~V2+7FQTZNGKE~5+21IQ.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/2SW~V2+7FQTZNGKE~5+21IQ.png)

#### 7.创建配置文件

创建名为vfio.conf的新文件

```Plain Text
sudo nano /etc/modprobe.d/vfio.conf
```

将步骤6中的设备ID添加到以下行：

```Plain Text
blacklist nouveau
blacklist snd_hda_intel
options vfio-pci ids=10aa:10bb,01cc:01ee
```

![+U__257Z+@QX_A+PLGP1X4O.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/+U__257Z+@QX_A+PLGP1X4O.png)

#### 8.更新现有配置

更新现有的initramfs

```Plain Text
sudo update-initramfs -u
```

![~1E+++WS48+S4JYK2V91TLJ.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/~1E+++WS48+S4JYK2V91TLJ.png)

#### 9.重启

#### 10.验证是否正常

输入命令：

```Plain Text
lspci -nnk
```

如果出现了“Kernel driver in use: nouveau” 或者“Kernel driver in use: snd_hda_intel”，则需要从头检查是否有遗漏或错误的步骤

参考文本：

```Plain Text
01:00.0 VGA compatible controller [0300]: NVIDIA Corporation TU117 [GeForce GTX 1650] [10aa:10bb] (rev a1)
    Subsystem: Micro-Star International Co., Ltd. [MSI] TU117 [GeForce GTX 1650] [0101:a1a1]
    Kernel modules: nvidiafb, nouveau
01:00.1 Audio device [0403]: NVIDIA Corporation Device [01cc:01ee] (rev a1)
    Subsystem: Micro-Star International Co., Ltd. [MSI] Device [0202:a2a2]
    Kernel modules: snd_hda_intel
```

![JTK+WQY55PF+08HEO~GBK+7.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/JTK+WQY55PF+08HEO~GBK+7.png)



# 八、在KVM中装载显卡

打开KVM虚拟机管理软件

![P+KFUFA@+WY$+BPS0AD7QS3.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/P+KFUFA@+WY$+BPS0AD7QS3.png)

点击打开

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 14.png)

添加硬件

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 15.png)

点击PCI主机设备

![image.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/image 16.png)

选择NVDIA设备，点击完成

![Q$3TMMX5A1S1MH+O4D86Y86.png](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/Q$3TMMX5A1S1MH+O4D86Y86.png)

添加完毕

![++O8+14REZQP6NQY++L++4E.jpg](针对基于Ubuntu系统搭建显卡直通的KVM虚拟机进行内存分析+ef84ff78-f05f-4982-acf2-a12cbca34504/++O8+14REZQP6NQY++L++4E.jpg)

CPU请设置为“host-passthrough”，并勾选手动设置CPU拓扑，将套接字和线程改为1，只更改核心数

启动虚拟机

在虚拟机中下载对应的显卡驱动进行安装

可以在添加硬件中添加USB硬件，选择鼠标和键盘添加，可以用一套独立的鼠标键盘单独操控虚拟机



# 九、编译环境搭建

最后需要安装一些指定的库来实现编译

以下指引仅供参考，请根据自行需要去安装运行库

#### 1.Rust和Cargo的编译环境安装

    ```Plain Text
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
    
    # 立即生效环境变量:ml-citation{ref="3,6" data="citationList"}
    source $HOME/.cargo/env
    ```

    ```Plain Text
    # 版本可能较旧:ml-citation{ref="6" data="citationList"}
    sudo apt install rustc cargo
    ```

#### 2.GLEW开发库和开发包安装

    ```Plain Text
    sudo apt-get install libglew-dev
    
    # 安装 GLFW3 开发包
    sudo apt install libglfw3-dev
    ```

    检查GLEW路径

    如有必要，修改Makefile文件内容

#### 3.编译文件

    在文件目录下执行以下命令编译源码

    ```Plain Text
    bash build.sh
    ```

    在 build 文件夹下执行以下命令运行程序

    ```Plain Text
    sudo ./wt_dma
    ```



# 十、一些可能存在的问题的解决方法

1.如果有明显的卡顿情况下

①关闭DLSS和DX12

②CPU核心数请保证在16大核及以上，或者大小核在24核心及以上

③如果依旧卡顿，尝试关闭战雷的Battleye

2.关闭侧边栏和顶部栏



未完待续……

