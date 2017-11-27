# This the code for free

def Release(release,name):
    if release == 1:
        print('release {}'.format(name))
        print('the process to release Zac is ready')
    else:
        print('cannot release')


if __name__ == '__main__':
    release_swith = int(input("please input free value, 1 for free 0 for not free"))
    release_name = input('please input release name')
    Release(release_swith,release_name)
