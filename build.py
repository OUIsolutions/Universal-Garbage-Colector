import Build.CToolKit as ct
from Build.exemple_build import create_exemples
from os import makedirs
from props import *

from Build.full_folder_zip import zip_folder


ct.generate_amalgamated_code(STARTER,OUTPUT)

if SIDE_EFFECT_FOLDER is None:
    SIDE_EFFECT_FOLDER = 'side_effect'

makedirs(SIDE_EFFECT_FOLDER,exist_ok=True)

test = ct.FolderTestPreset(
    folder=TEST_FOLDER,
    side_effect_folder=SIDE_EFFECT_FOLDER,
    use_valgrind=USE_VALGRIND
)

test.generate_ouptut(reconstruct=RECONSTRUCT)
test.start_test()

create_exemples()
ct.include_code_in_markdown('README.md',save_file=True)
zip_folder('CHashManipulator')
