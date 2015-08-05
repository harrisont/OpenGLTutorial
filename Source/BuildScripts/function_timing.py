import time


def time_function(function, *args, **kwargs):
    """
    :return: (<function-call-result>, <function-call-duration-seconds>)
    """
    start = time.time()
    result = function(*args, **kwargs)
    end = time.time()
    return result, (end - start)


def get_duration_str(duration):
    if duration < 0.01:
        return "{:.2n} milliseconds".format(duration*1000)
    else:
        return "{:.2n} seconds".format(duration)
