import os

test_dir = os.path.split(__file__)[-2]
proj_dir = os.path.split(test_dir)[-2]
bin_dir = os.path.join(proj_dir, 'build\\Debug')

reader_exe = os.path.join(bin_dir, 'reader.exe')
writer_exe = os.path.join(bin_dir, 'writer.exe')

# case 'Normal communication'
print('case 1')
with open('data.txt', 'w') as f:
    f.write('John Watson Doctor')

assert os.system(writer_exe + ' data.txt') == 0, 'writer failed'
assert os.system(reader_exe + ' person.bin') == 0, 'reader failed'
assert os.path.exists('data.txt'), "data.txt wasn't generated"
os.remove('data.txt')
assert os.path.exists('person.bin'), "person.bin wasn't generated"
os.remove('person.bin')

print('\n')

# case 'Input validation in reader'
print('case 2')
with open('data.txt', 'w') as f:
    f.write('John Watson Doctr')

assert os.system(writer_exe + ' data.txt') != 0, 'writer accepted an invalid input'
assert not os.path.exists('person.bin'), 'data.txt was generated nonetheless'
os.remove('data.txt')
