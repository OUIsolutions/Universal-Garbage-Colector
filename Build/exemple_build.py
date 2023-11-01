

from shutil import copytree
from shutil import rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir,dirname
from props import *



def move_all_c(current_path:str):
    elements = listdir(current_path)
    for e in elements:
        path = f'{current_path}/{e}'

        if isdir(path):
            move_all_c(path)
            continue

        if e.endswith('.c') or e.endswith('.cpp'):
            with open(path,'r') as arq:
                content = arq.read()

                content = content.replace(f'../../../{OUTPUT}',OUTPUT)
                content = content.replace(f'../../../../{OUTPUT}',OUTPUT)
                content = content.replace(f'../../{OUTPUT}',OUTPUT)
                content = content.replace(f'../{OUTPUT}',OUTPUT)

            
            name =dirname(path).replace('T_','').replace(TEST_FOLDER,EXEMPLE_FOLDER)
            makedirs('/'.join(name.split('/')[0:-1]),exist_ok=True)
            with open(f'{name}.c','w') as arq2:
                arq2.write(content)



def create_exemples():
    rmtree(EXEMPLE_FOLDER,ignore_errors=True)
    makedirs(EXEMPLE_FOLDER)
    move_all_c(TEST_FOLDER)