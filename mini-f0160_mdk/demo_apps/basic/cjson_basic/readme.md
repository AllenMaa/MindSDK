# cjson_basic

## 实验过程

+ 打印 cJSON 版本。
+ 创建基本的 JSON 实例并打印该实例。
+ 创建字符串 JSON 数组并打印该数组。
+ 创建包含三个 JSON 数组的 JSON 数组并打印该数组。
+ 创建仅包含一个 JSON 类型数据的 JSON 实例并打印该实例。
+ 创建包含两个 JSON 实例的 JSON 数组并打印该数组。
+ 创建仅包含一个数值类型数据的 JSON 实例并打印该实例。

## 实验结果

cjson_basic demo.
Version: 1.7.15
{
        "name": "Jack (\"Bee\") Nimble",
        "format":       {
                "type": "rect",
                "width":        1920,
                "height":       1080,
                "interlace":    false,
                "frame rate":   24
        }
}
["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
[[0, -1, 0], [1, 0, 0], [0, 0, 1]]
{
        "Image":        {
                "Width":        800,
                "Height":       600,
                "Title":        "View from 15th Floor",
                "Thumbnail":    {
                        "Url":  "http:/*www.example.com/image/481989943",
                        "Height":       125,
                        "Width":        "100"
                },
                "IDs":  [116, 943, 234, 38793]
        }
}
[{
                "precision":    "zip",
                "Latitude":     37.7668,
                "Longitude":    -122.3959,
                "Address":      "",
                "City": "SAN FRANCISCO",
                "State":        "CA",
                "Zip":  "94107",
                "Country":      "US"
        }, {
                "precision":    "zip",
                "Latitude":     37.371991,
                "Longitude":    -122.026,
                "Address":      "",
                "City": "SUNNYVALE",
                "State":        "CA",
                "Zip":  "94085",
                "Country":      "US"
        }]
{
        "number":       0
}
