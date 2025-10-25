import example

print("== Owned object ==")
f1 = example.make_owned(42)
f1.hello()
del f1
print("f1 deleted")

print("== Borrowed object ==")
f2 = example.get_borrowed()
f2.hello()
del f2
print("f2 deleted")
