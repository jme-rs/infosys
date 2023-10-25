# C言語でのコマンド開発


## 工夫した点

- フォーマットを統一した
- 関数を小分けにしてメンテナンス性を向上させた
- テストを行い条件分岐を検証した

### Excersize 6 mystrcmp

- きれいに書けた
```c
int is_correct_args(int args, char *argv[])
{
    return (args == 2 && is_number(argv[1]))
        || (args == 3 && is_number(argv[1]) && is_number(argv[2]));
}
```
