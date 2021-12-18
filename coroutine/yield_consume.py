def concat_string(base_input):
    print(base_input, "received")
    while True:
        print("000")
        appendix = (yield)                  # yield capture
        print("111")
        yield base_input + " " + appendix   # yield return


if __name__ == "__main__":
    concat = concat_string("Base")  # no go into coroutine yet
    print("===")
    concat.__next__()   # advance & pause at first yield statement [either yield capture or return]
    print("333")
    res = concat.send("X")  # feed value, advance & pause at next yield
    print("444")
    print(res)
    concat.__next__()
    print("555")

    concat.close()