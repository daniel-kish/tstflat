import os
import sys

test_dir = os.path.split(__file__)[-2]
proj_dir = os.path.split(test_dir)[-2]
bin_dir = os.path.join(proj_dir, 'build\\Debug')

reader_exe = os.path.join(bin_dir, 'reader.exe')
writer_exe = os.path.join(bin_dir, 'writer.exe')
book_reader_exe = os.path.join(bin_dir, 'book_reader.exe')

if '1' in sys.argv:
    # case 'Unknown enum rejection'
    print('case 1')
    with open('data.txt', 'w') as f:
        f.write('Le Corbusier Architect')

    assert os.path.exists('data.txt'), "data.txt wasn't generated"
    assert os.system(writer_exe + ' data.txt') == 0, 'writer failed'
    assert os.path.exists('person.bin'), "person.bin wasn't generated"
    assert os.system(reader_exe + ' person.bin') != 0, 'reader succeeded'
    os.remove('person.bin')
    os.remove('data.txt')

    print('\n')

if '2' in sys.argv:
    # case 'Input validation in reader'
    print('case 2')
    with open('data.txt', 'w') as f:
        f.write('John Watson Doctr')

    assert os.system(writer_exe + ' data.txt') != 0, 'writer accepted an invalid input'
    assert not os.path.exists('person.bin'), 'person.bin was generated nonetheless'
    os.remove('data.txt')

if '3' in sys.argv:
    # case 'Input validation in reader'
    print('case 3')
    with open('data.txt', 'w') as f:
        f.write('Bjarne Stroustrup Developer Liar 1/5/2001')

    assert os.path.exists('data.txt'), "data.txt wasn't generated"
    assert os.system(writer_exe + ' data.txt') == 0, 'writer failed'
    assert os.path.exists('person.bin'), "person.bin wasn't generated"
    assert os.system(reader_exe + ' person.bin') == 0, 'reader failed'
    assert os.path.exists('book.bin'), "book.bin wasn't generated"
    assert os.system(book_reader_exe + ' book.bin') == 0, 'book_reader_exe failed'

    os.remove('data.txt')
    os.remove('person.bin')
    os.remove('book.bin')

if '4' in sys.argv:
    # case 'No book'
    print('case 4')
    with open('data.txt', 'w') as f:
        f.write('John Doe Worker')

    assert os.path.exists('data.txt'), "data.txt wasn't generated"
    assert os.system(writer_exe + ' data.txt') == 0, 'writer failed'
    assert os.path.exists('person.bin'), "person.bin wasn't generated"
    assert os.system(reader_exe + ' person.bin') == 0, "reader failed"
    assert not os.path.exists('book.bin'), "book.bin was generated"

    os.remove('data.txt')
    os.remove('person.bin')
