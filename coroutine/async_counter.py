# %%
import asyncio
import time
import random

"""
I don't see any scenario in trading engine where coroutine is necessary.
Probably a little useful for fitting? But not necessary study it!

Functions defined as async def are coroutines.
Must await to call coroutine.
Forget about using yield in coroutine!
Can only use await inside the body of coroutine.
"""

c = (
    "\033[0m",  # End of color
    "\033[36m",  # Cyan
    "\033[91m",  # Red
    "\033[35m",  # Magenta
)


async def makerandom(idx: int, threshold: int = 7) -> int:
    print(c[idx + 1] + f"initiated {idx} ")
    i = random.randint(0, 10)
    while i <= threshold:
        print(c[idx + 1] + f"RETRY {idx}", i)
        await asyncio.sleep(idx + 1)
        i = random.randint(0, 10)

    print(c[idx + 1] + f"STOP@ {idx}", i)
    return i


async def main():
    res = await asyncio.gather(*[makerandom(i) for i in range(3)])
    return res


s = time.perf_counter()
res = asyncio.run(main())  # res can be [9, 10, 10]
elapsed = time.perf_counter() - s
print(elapsed)
