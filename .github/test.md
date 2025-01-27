# Rod Cutting Problem Test Cases

## Test Case 1: Basic Fit

**Command:**

```bash
./main 5
```

**Input:**

```
1, 2
2, 5
```

**Expected Output:**

```
2 @ 2 = 10
1 @ 1 = 2
Remainder: 0
Value: 12
```

---

## Test Case 2: No Solution Available

**Command:**

```bash
./main 4
```

**Input:**

```
5, 10
6, 15
```

**Expected Output:**

```
Remainder: 4
Value: 0
```

---

## Test Case 3: Optimal Solution Choosing

**Command:**

```bash
./main 20
```

**Input:**

```
5, 10
10, 25
```

**Expected Output:**

```
2 @ 10 = 50
Remainder: 0
Value: 50
```

---