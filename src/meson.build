conf_data = configuration_data()
conf_data.set('destruction_level', get_option('destruction_level'))
configure_file(input : 'options.h.in', output : 'options.h', configuration : conf_data)

shared_library('troll', 'main.c', link_args: ['-ldl'])

# vim: ft=cmake
