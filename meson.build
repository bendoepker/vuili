project(
  'vuili',
  'c',
)

src = [
  'src/vuili.c'
]

inc = [
  'src/vuili.h',
  'src/internal.h',
  'src/config.h',
  'src/viewport.h'
]

fs = import('fs')
fs.copyfile('src/vuili.h')

library(
  'vuili',
  sources: src,
)
