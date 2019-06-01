import os

test_dir = os.path.split(__file__)[-2]
proj_dir = os.path.split(test_dir)[-2]
bin_dir = os.path.join(proj_dir, 'build\\Debug')

reader_exe = os.path.join(bin_dir, 'reader.exe')
writer_exe = os.path.join(bin_dir, 'writer.exe')

with open('data.txt', 'w') as f:
    f.write('John Watson Doctor')

os.system(writer_exe + ' data.txt')
os.system(reader_exe + ' person.bin')

os.remove('data.txt')
os.remove('person.bin')
