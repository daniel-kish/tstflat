import os

test_dir = os.path.split(__file__)[-2]
proj_dir = os.path.split(test_dir)[-2]
bin_dir = os.path.join(proj_dir, 'build\\Debug')

reader_exe = os.path.join(bin_dir, 'reader.exe')
writer_exe = os.path.join(bin_dir, 'writer.exe')

os.system(reader_exe + ' data.txt')
os.system(writer_exe + ' person.bin')
