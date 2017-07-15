import os.path as path

project_name = 'ChipSelect'

target = '{}_test'.format(project_name)
target = path.join('out', target)

env = Environment(
    CXX='g++-7',
    CC='gcc-7',
    CXXFLAGS='-std=c++17 -Wall -Wextra',
    LIBS='pthread'
)

gtest = 'test/googletest/googletest'

sources = {
    'implementation': Glob('src/*.cpp'),
    'test': Glob('test/*.cpp'),
    'gtest': [path.join(gtest, 'src/gtest-all.cc')],
}

includes = {
    'implementation': ['include'],
    'test': ['include', '.', path.join(gtest, 'include')],
    'gtest': [gtest, path.join(gtest, 'include')],
}

cxxflags = {
    'implementation': env['CXXFLAGS'],
    'test': env['CXXFLAGS'] + ' -Wno-missing-field-initializers',
    'gtest': env['CXXFLAGS'],
}

objects = dict()
for key in sources.keys():
    objects[key] = env.Object(sources[key], CPPPATH=includes[key], CXXFLAGS=cxxflags[key])

NoClean(objects['gtest'])

objects_ = list()
for key in objects.keys():
    objects_ += objects[key]

Default(target)

env.Program(target, objects_)
