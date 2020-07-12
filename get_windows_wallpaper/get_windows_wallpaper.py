import os
import shutil
from PIL import Image


# 墙纸分类,是否是pc的桌面,若不是,那就是手机桌面
def is_pc(photo_path):
    img = Image.open(photo_path)
    return True if img.width/img.height > 1 else False


# 获取墙纸并分类
def get_wallpaper(from_path, to_path, f_ext):
    if from_path == to_path:
        print("Error: to_path and from_path cannot be the same")
        exit()
    photo_list = os.listdir(from_path)
    pc_path = os.path.join(to_path, 'pc')
    phone_path = os.path.join(to_path, 'phone')
    # 判断相关路径是否存在,若不存在则新建路径
    if not os.path.exists(pc_path):
        os.makedirs(pc_path)
    if not os.path.exists(phone_path):
        os.mkdir(phone_path)
    for f in photo_list:
        new_name = f+f_ext
        photo_path = os.path.join(from_path, f)
        if is_pc(photo_path):
            # https://www.cnblogs.com/liuqi-beijing/p/6228561.html
            if not os.path.exists(os.path.join(pc_path, new_name)):
                shutil.copy(photo_path, os.path.join(pc_path, new_name))
        else:
            if not os.path.exists(os.path.join(phone_path, new_name)):
                shutil.copy(photo_path, os.path.join(phone_path, new_name))


if __name__ == "__main__":
    # 壁纸所在路径
    from_path = os.environ.get(
        r'localappdata')+r'\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\Assets'
    # 转移到该路径
    to_path = r"E:\\tmp\\photo"
    # 文件格式
    f_ext = '.jpg'

    get_wallpaper(from_path, to_path, f_ext)
