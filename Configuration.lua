is_full_screen = false--true--true -- full screen

default_frame_rate =  45

default_rate = 0.006 -- 시작할 때의 이자.

rate_rate = 0.634 -- 이자가 오르는 속도

default_limit = 100000 --  시작할 때의 카드 한도

limit_rate = 100000 --  한도가 오르는 속도

start_grade = 9 -- 9 is B+


function lua_event_handler(event_id)
    io.stderr:write("here is lua file \n")
    print_message_1("hahahahaha")
    print_message_2("hahahahaha")
end
