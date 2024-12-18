# SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-only

function(target_enable_warnings TARG)
    if(MSVC)
      if(NOT ENABLE_WERROR)
          target_compile_options(${TARG} PRIVATE /W4)
      else()
          target_compile_options(${TARG} PRIVATE /W4 /WX)
      endif()
    else()
      if(NOT ENABLE_WERROR)
          target_compile_options(${TARG} PRIVATE -Wall -Wextra -Wpedantic)
      else()
          target_compile_options(${TARG} PRIVATE -Wall -Wextra -Wpedantic -Werror)
      endif()
    endif()
endfunction()
