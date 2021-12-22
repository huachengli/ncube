//
// Created by huacheng on 12/16/21.
//

#ifndef NCUBE_PP_MACROS_H
#define NCUBE_PP_MACROS_H

#define PP_CONCAT(A, B) PP_CONCAT_IMPL(A, B)
#define PP_CONCAT_IMPL(A, B) A##B

#define PP_REMOVE_PARENS(T) PP_REMOVE_PARENS_IMPL T
#define PP_REMOVE_PARENS_IMPL(...) __VA_ARGS__

// some special characters
#define PP_COMMA() ,
#define PP_LPAREN() (
#define PP_RPAREN() )
#define PP_EMPTY()
#define PP_STAR() *

// check
#define PP_EMPTY_V(...)
#define PP_IS_PARENS(SYMBOL) PP_IS_EMPTY(PP_EMPTY_V SYMBOL)

// Index
#define PP_GET_N(N, ...) PP_CONCAT(PP_GET_N_, N)(__VA_ARGS__)
#define PP_GET_TUPLE(N, T) PP_GET_N(N, PP_REMOVE_PARENS(T))
#define PP_GET_N_0(_0, ...) _0
#define PP_GET_N_1(_0, _1, ...) _1
#define PP_GET_N_2(_0, _1, _2, ...) _2
#define PP_GET_N_3(_0, _1, _2, _3, ...) _3
#define PP_GET_N_4(_0, _1, _2, _3, _4, ...) _4
#define PP_GET_N_5(_0, _1, _2, _3, _4, _5, ...) _5
#define PP_GET_N_6(_0, _1, _2, _3, _4, _5, _6, ...) _6
#define PP_GET_N_7(_0, _1, _2, _3, _4, _5, _6, _7, ...) _7
#define PP_GET_N_8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _8

// Bool operation
#define PP_NOT(N) PP_CONCAT(PP_NOT_, N)
#define PP_NOT_0 1
#define PP_NOT_1 0

#define PP_AND(A, B) PP_CONCAT(PP_AND_, PP_CONCAT(A, B))
#define PP_AND_00 0
#define PP_AND_01 0
#define PP_AND_10 0
#define PP_AND_11 1

#define PP_BOOL(N) PP_CONCAT(PP_BOOL_, N)
#define PP_BOOL_0 0
#define PP_BOOL_1 1
#define PP_BOOL_2 1

// if-else
#define PP_IF(PRED, THEN, ELSE) PP_CONCAT(PP_IF_, PP_BOOL(PRED))(THEN, ELSE)
#define PP_IF_1(THEN, ELSE) THEN
#define PP_IF_0(THEN, ELSE) ELSE
#define PP_COMMA_IF(N) PP_IF(N, PP_COMMA, PP_EMPTY)()
#define PP_STAR_IF(N) PP_IF(N, PP_STAR, PP_EMPTY)()

// if-empty
#define PP_IS_EMPTY(...)                                      \
  PP_AND(PP_AND(PP_NOT(PP_HAS_COMMA(__VA_ARGS__)),            \
                PP_NOT(PP_HAS_COMMA(__VA_ARGS__()))),         \
         PP_AND(PP_NOT(PP_HAS_COMMA(PP_COMMA_V __VA_ARGS__)), \
                PP_HAS_COMMA(PP_COMMA_V __VA_ARGS__())))
#define PP_HAS_COMMA(...) PP_GET_N_8(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 0, 0)
#define PP_COMMA_V(...) ,

// _VA_OPT_
#define PP_VA_OPT_COMMA(...) PP_COMMA_IF(PP_NOT(PP_IS_EMPTY(__VA_ARGS__)))
#define PP_NARG(...) PP_GET_N(8, __VA_ARGS__ PP_VA_OPT_COMMA(__VA_ARGS__) 8, 7, 6, 5, 4, 3, 2, 1,0)

// for each
#define PP_FOR_EACH(DO, CTX, ...) \
  PP_CONCAT(PP_FOR_EACH_, PP_NARG(__VA_ARGS__))(DO, CTX, 0, __VA_ARGS__)
#define PP_FOR_EACH_0(DO, CTX, IDX, ...)
#define PP_FOR_EACH_1(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)
#define PP_FOR_EACH_2(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_1(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_3(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_2(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_4(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_3(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_5(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_4(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_6(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_5(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_7(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_6(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_8(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_7(DO, CTX, PP_INC(IDX), __VA_ARGS__)
// inner for-earch
#define PP_FOR_EACH_INNER(DO, CTX, ...) \
  PP_CONCAT(PP_FOR_EACH_INNER_, PP_NARG(__VA_ARGS__))(DO, CTX, 0, __VA_ARGS__)
#define PP_FOR_EACH_INNER_0(DO, CTX, IDX, ...)
#define PP_FOR_EACH_INNER_1(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)
#define PP_FOR_EACH_INNER_2(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_1(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_3(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_2(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_4(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_3(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_5(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_4(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_6(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_5(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_7(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_6(DO, CTX, PP_INC(IDX), __VA_ARGS__)
#define PP_FOR_EACH_INNER_8(DO, CTX, IDX, VAR, ...) DO(VAR, IDX, CTX)     \
  PP_FOR_EACH_INNER_7(DO, CTX, PP_INC(IDX), __VA_ARGS__)

// while
#define PP_WHILE PP_WHILE_1
#define PP_WHILE_1(PRED, OP, VAL)              \
  PP_IF(PRED(VAL), PP_WHILE_2, VAL PP_EMPTY_V) \
  (PRED, OP, PP_IF(PRED(VAL), OP, PP_EMPTY_V)(VAL))
#define PP_WHILE_2(PRED, OP, VAL)              \
  PP_IF(PRED(VAL), PP_WHILE_3, VAL PP_EMPTY_V) \
  (PRED, OP, PP_IF(PRED(VAL), OP, PP_EMPTY_V)(VAL))
#define PP_WHILE_3(PRED, OP, VAL)              \
  PP_IF(PRED(VAL), PP_WHILE_4, VAL PP_EMPTY_V) \
  (PRED, OP, PP_IF(PRED(VAL), OP, PP_EMPTY_V)(VAL))
#define PP_WHILE_4(PRED, OP, VAL)              \
  PP_IF(PRED(VAL), PP_WHILE_5, VAL PP_EMPTY_V) \
  (PRED, OP, PP_IF(PRED(VAL), OP, PP_EMPTY_V)(VAL))
#define PP_WHILE_5(PRED, OP, VAL)              \
  PP_IF(PRED(VAL), PP_WHILE_6, VAL PP_EMPTY_V) \
  (PRED, OP, PP_IF(PRED(VAL), OP, PP_EMPTY_V)(VAL))

// compare
#define PP_CMP(X, Y) PP_WHILE(PP_CMP_P, PP_CMP_O, (X, Y))
#define PP_CMP_P(V) \
  PP_AND(PP_BOOL(PP_GET_TUPLE(0, V)), PP_BOOL(PP_GET_TUPLE(1, V)))
#define PP_CMP_O(V) (PP_DEC(PP_GET_TUPLE(0, V)), PP_DEC(PP_GET_TUPLE(1, V)))

#define PP_EQUAL(X, Y) PP_IDENTITY(PP_EQUAL_IMPL PP_CMP(X, Y))
#define PP_EQUAL_IMPL(RX, RY) PP_AND(PP_NOT(PP_BOOL(RX)), PP_NOT(PP_BOOL(RY)))
#define PP_LESS(X, Y) PP_IDENTITY(PP_LESS_IMPL PP_CMP(X, Y))
#define PP_LESS_IMPL(RX, RY) PP_AND(PP_NOT(PP_BOOL(RX)), PP_BOOL(RY))
#define PP_MIN(X, Y) PP_IF(PP_LESS(X, Y), X, Y)
#define PP_MAX(X, Y) PP_IF(PP_LESS(X, Y), Y, X)
// ...

// INC and DEC
#define PP_INC(N) PP_CONCAT(PP_INC_, N)
#define PP_INC_0 1
#define PP_INC_1 2
#define PP_INC_2 3
#define PP_INC_3 4
#define PP_INC_4 5
#define PP_INC_5 6
#define PP_INC_6 7
#define PP_INC_7 8
#define PP_INC_8 9
#define PP_INC_9 10
#define PP_INC_10 11
#define PP_INC_11 12
#define PP_INC_12 13
#define PP_INC_13 14
#define PP_INC_14 15
#define PP_INC_15 16
#define PP_INC_16 17
#define PP_INC_17 18
#define PP_INC_18 19
#define PP_INC_19 20
#define PP_INC_20 21
#define PP_INC_21 22
#define PP_INC_22 23
#define PP_INC_23 24
#define PP_INC_24 25
#define PP_INC_25 26
#define PP_INC_26 27
#define PP_INC_27 28
#define PP_INC_28 29
#define PP_INC_29 30
#define PP_INC_30 31
#define PP_INC_31 32
#define PP_INC_32 33
#define PP_INC_33 34
#define PP_INC_34 35
#define PP_INC_35 36
#define PP_INC_36 37
#define PP_INC_37 38
#define PP_INC_38 39
#define PP_INC_39 40
#define PP_INC_40 41
#define PP_INC_41 42
#define PP_INC_42 43
#define PP_INC_43 44
#define PP_INC_44 45
#define PP_INC_45 46
#define PP_INC_46 47
#define PP_INC_47 48
#define PP_INC_48 49
#define PP_INC_49 50
#define PP_INC_50 51
#define PP_INC_51 52
#define PP_INC_52 53
#define PP_INC_53 54
#define PP_INC_54 55
#define PP_INC_55 56
#define PP_INC_56 57
#define PP_INC_57 58
#define PP_INC_58 59
#define PP_INC_59 60
#define PP_INC_60 61
#define PP_INC_61 62
#define PP_INC_62 63
#define PP_INC_63 64
#define PP_INC_64 65
#define PP_INC_65 66
#define PP_INC_66 67
#define PP_INC_67 68
#define PP_INC_68 69
#define PP_INC_69 70
#define PP_INC_70 71
#define PP_INC_71 72
#define PP_INC_72 73
#define PP_INC_73 74
#define PP_INC_74 75
#define PP_INC_75 76
#define PP_INC_76 77
#define PP_INC_77 78
#define PP_INC_78 79
#define PP_INC_79 80
#define PP_INC_80 81
#define PP_INC_81 82
#define PP_INC_82 83
#define PP_INC_83 84
#define PP_INC_84 85
#define PP_INC_85 86
#define PP_INC_86 87
#define PP_INC_87 88
#define PP_INC_88 89
#define PP_INC_89 90
#define PP_INC_90 91
#define PP_INC_91 92
#define PP_INC_92 93
#define PP_INC_93 94
#define PP_INC_94 95
#define PP_INC_95 96
#define PP_INC_96 97
#define PP_INC_97 98
#define PP_INC_98 99
#define PP_INC_99 100
#define PP_INC_100 101
#define PP_INC_101 102
#define PP_INC_102 103
#define PP_INC_103 104
#define PP_INC_104 105
#define PP_INC_105 106
#define PP_INC_106 107
#define PP_INC_107 108
#define PP_INC_108 109
#define PP_INC_109 110
#define PP_INC_110 111
#define PP_INC_111 112
#define PP_INC_112 113
#define PP_INC_113 114
#define PP_INC_114 115
#define PP_INC_115 116
#define PP_INC_116 117
#define PP_INC_117 118
#define PP_INC_118 119
#define PP_INC_119 120
#define PP_INC_120 121
#define PP_INC_121 122
#define PP_INC_122 123
#define PP_INC_123 124
#define PP_INC_124 125
#define PP_INC_125 126
#define PP_INC_126 127
#define PP_INC_127 128
#define PP_INC_128 129
#define PP_INC_129 130
#define PP_INC_130 131
#define PP_INC_131 132
#define PP_INC_132 133
#define PP_INC_133 134
#define PP_INC_134 135
#define PP_INC_135 136
#define PP_INC_136 137
#define PP_INC_137 138
#define PP_INC_138 139
#define PP_INC_139 140
#define PP_INC_140 141
#define PP_INC_141 142
#define PP_INC_142 143
#define PP_INC_143 144
#define PP_INC_144 145
#define PP_INC_145 146
#define PP_INC_146 147
#define PP_INC_147 148
#define PP_INC_148 149
#define PP_INC_149 150
#define PP_INC_150 151
#define PP_INC_151 152
#define PP_INC_152 153
#define PP_INC_153 154
#define PP_INC_154 155
#define PP_INC_155 156
#define PP_INC_156 157
#define PP_INC_157 158
#define PP_INC_158 159
#define PP_INC_159 160
#define PP_INC_160 161
#define PP_INC_161 162
#define PP_INC_162 163
#define PP_INC_163 164
#define PP_INC_164 165
#define PP_INC_165 166
#define PP_INC_166 167
#define PP_INC_167 168
#define PP_INC_168 169
#define PP_INC_169 170
#define PP_INC_170 171
#define PP_INC_171 172
#define PP_INC_172 173
#define PP_INC_173 174
#define PP_INC_174 175
#define PP_INC_175 176
#define PP_INC_176 177
#define PP_INC_177 178
#define PP_INC_178 179
#define PP_INC_179 180
#define PP_INC_180 181
#define PP_INC_181 182
#define PP_INC_182 183
#define PP_INC_183 184
#define PP_INC_184 185
#define PP_INC_185 186
#define PP_INC_186 187
#define PP_INC_187 188
#define PP_INC_188 189
#define PP_INC_189 190
#define PP_INC_190 191
#define PP_INC_191 192
#define PP_INC_192 193
#define PP_INC_193 194
#define PP_INC_194 195
#define PP_INC_195 196
#define PP_INC_196 197
#define PP_INC_197 198
#define PP_INC_198 199
#define PP_INC_199 200
#define PP_INC_200 201
#define PP_INC_201 202
#define PP_INC_202 203
#define PP_INC_203 204
#define PP_INC_204 205
#define PP_INC_205 206
#define PP_INC_206 207
#define PP_INC_207 208
#define PP_INC_208 209
#define PP_INC_209 210
#define PP_INC_210 211
#define PP_INC_211 212
#define PP_INC_212 213
#define PP_INC_213 214
#define PP_INC_214 215
#define PP_INC_215 216
#define PP_INC_216 217
#define PP_INC_217 218
#define PP_INC_218 219
#define PP_INC_219 220
#define PP_INC_220 221
#define PP_INC_221 222
#define PP_INC_222 223
#define PP_INC_223 224
#define PP_INC_224 225
#define PP_INC_225 226
#define PP_INC_226 227
#define PP_INC_227 228
#define PP_INC_228 229
#define PP_INC_229 230
#define PP_INC_230 231
#define PP_INC_231 232
#define PP_INC_232 233
#define PP_INC_233 234
#define PP_INC_234 235
#define PP_INC_235 236
#define PP_INC_236 237
#define PP_INC_237 238
#define PP_INC_238 239
#define PP_INC_239 240
#define PP_INC_240 241
#define PP_INC_241 242
#define PP_INC_242 243
#define PP_INC_243 244
#define PP_INC_244 245
#define PP_INC_245 246
#define PP_INC_246 247
#define PP_INC_247 248
#define PP_INC_248 249
#define PP_INC_249 250
#define PP_INC_250 251
#define PP_INC_251 252
#define PP_INC_252 253
#define PP_INC_253 254
#define PP_INC_254 255
#define PP_INC_255 256

#define PP_DEC(N) PP_CONCAT(PP_DEC_, N)
#define PP_DEC_1 0
#define PP_DEC_2 1
#define PP_DEC_3 2
#define PP_DEC_4 3
#define PP_DEC_5 4
#define PP_DEC_6 5
#define PP_DEC_7 6
#define PP_DEC_8 7
#define PP_DEC_9 8
#define PP_DEC_10 9
#define PP_DEC_11 10
#define PP_DEC_12 11
#define PP_DEC_13 12
#define PP_DEC_14 13
#define PP_DEC_15 14
#define PP_DEC_16 15
#define PP_DEC_17 16
#define PP_DEC_18 17
#define PP_DEC_19 18
#define PP_DEC_20 19
#define PP_DEC_21 20
#define PP_DEC_22 21
#define PP_DEC_23 22
#define PP_DEC_24 23
#define PP_DEC_25 24
#define PP_DEC_26 25
#define PP_DEC_27 26
#define PP_DEC_28 27
#define PP_DEC_29 28
#define PP_DEC_30 29
#define PP_DEC_31 30
#define PP_DEC_32 31
#define PP_DEC_33 32
#define PP_DEC_34 33
#define PP_DEC_35 34
#define PP_DEC_36 35
#define PP_DEC_37 36
#define PP_DEC_38 37
#define PP_DEC_39 38
#define PP_DEC_40 39
#define PP_DEC_41 40
#define PP_DEC_42 41
#define PP_DEC_43 42
#define PP_DEC_44 43
#define PP_DEC_45 44
#define PP_DEC_46 45
#define PP_DEC_47 46
#define PP_DEC_48 47
#define PP_DEC_49 48
#define PP_DEC_50 49
#define PP_DEC_51 50
#define PP_DEC_52 51
#define PP_DEC_53 52
#define PP_DEC_54 53
#define PP_DEC_55 54
#define PP_DEC_56 55
#define PP_DEC_57 56
#define PP_DEC_58 57
#define PP_DEC_59 58
#define PP_DEC_60 59
#define PP_DEC_61 60
#define PP_DEC_62 61
#define PP_DEC_63 62
#define PP_DEC_64 63
#define PP_DEC_65 64
#define PP_DEC_66 65
#define PP_DEC_67 66
#define PP_DEC_68 67
#define PP_DEC_69 68
#define PP_DEC_70 69
#define PP_DEC_71 70
#define PP_DEC_72 71
#define PP_DEC_73 72
#define PP_DEC_74 73
#define PP_DEC_75 74
#define PP_DEC_76 75
#define PP_DEC_77 76
#define PP_DEC_78 77
#define PP_DEC_79 78
#define PP_DEC_80 79
#define PP_DEC_81 80
#define PP_DEC_82 81
#define PP_DEC_83 82
#define PP_DEC_84 83
#define PP_DEC_85 84
#define PP_DEC_86 85
#define PP_DEC_87 86
#define PP_DEC_88 87
#define PP_DEC_89 88
#define PP_DEC_90 89
#define PP_DEC_91 90
#define PP_DEC_92 91
#define PP_DEC_93 92
#define PP_DEC_94 93
#define PP_DEC_95 94
#define PP_DEC_96 95
#define PP_DEC_97 96
#define PP_DEC_98 97
#define PP_DEC_99 98
#define PP_DEC_100 99
#define PP_DEC_101 100
#define PP_DEC_102 101
#define PP_DEC_103 102
#define PP_DEC_104 103
#define PP_DEC_105 104
#define PP_DEC_106 105
#define PP_DEC_107 106
#define PP_DEC_108 107
#define PP_DEC_109 108
#define PP_DEC_110 109
#define PP_DEC_111 110
#define PP_DEC_112 111
#define PP_DEC_113 112
#define PP_DEC_114 113
#define PP_DEC_115 114
#define PP_DEC_116 115
#define PP_DEC_117 116
#define PP_DEC_118 117
#define PP_DEC_119 118
#define PP_DEC_120 119
#define PP_DEC_121 120
#define PP_DEC_122 121
#define PP_DEC_123 122
#define PP_DEC_124 123
#define PP_DEC_125 124
#define PP_DEC_126 125
#define PP_DEC_127 126
#define PP_DEC_128 127
#define PP_DEC_129 128
#define PP_DEC_130 129
#define PP_DEC_131 130
#define PP_DEC_132 131
#define PP_DEC_133 132
#define PP_DEC_134 133
#define PP_DEC_135 134
#define PP_DEC_136 135
#define PP_DEC_137 136
#define PP_DEC_138 137
#define PP_DEC_139 138
#define PP_DEC_140 139
#define PP_DEC_141 140
#define PP_DEC_142 141
#define PP_DEC_143 142
#define PP_DEC_144 143
#define PP_DEC_145 144
#define PP_DEC_146 145
#define PP_DEC_147 146
#define PP_DEC_148 147
#define PP_DEC_149 148
#define PP_DEC_150 149
#define PP_DEC_151 150
#define PP_DEC_152 151
#define PP_DEC_153 152
#define PP_DEC_154 153
#define PP_DEC_155 154
#define PP_DEC_156 155
#define PP_DEC_157 156
#define PP_DEC_158 157
#define PP_DEC_159 158
#define PP_DEC_160 159
#define PP_DEC_161 160
#define PP_DEC_162 161
#define PP_DEC_163 162
#define PP_DEC_164 163
#define PP_DEC_165 164
#define PP_DEC_166 165
#define PP_DEC_167 166
#define PP_DEC_168 167
#define PP_DEC_169 168
#define PP_DEC_170 169
#define PP_DEC_171 170
#define PP_DEC_172 171
#define PP_DEC_173 172
#define PP_DEC_174 173
#define PP_DEC_175 174
#define PP_DEC_176 175
#define PP_DEC_177 176
#define PP_DEC_178 177
#define PP_DEC_179 178
#define PP_DEC_180 179
#define PP_DEC_181 180
#define PP_DEC_182 181
#define PP_DEC_183 182
#define PP_DEC_184 183
#define PP_DEC_185 184
#define PP_DEC_186 185
#define PP_DEC_187 186
#define PP_DEC_188 187
#define PP_DEC_189 188
#define PP_DEC_190 189
#define PP_DEC_191 190
#define PP_DEC_192 191
#define PP_DEC_193 192
#define PP_DEC_194 193
#define PP_DEC_195 194
#define PP_DEC_196 195
#define PP_DEC_197 196
#define PP_DEC_198 197
#define PP_DEC_199 198
#define PP_DEC_200 199
#define PP_DEC_201 200
#define PP_DEC_202 201
#define PP_DEC_203 202
#define PP_DEC_204 203
#define PP_DEC_205 204
#define PP_DEC_206 205
#define PP_DEC_207 206
#define PP_DEC_208 207
#define PP_DEC_209 208
#define PP_DEC_210 209
#define PP_DEC_211 210
#define PP_DEC_212 211
#define PP_DEC_213 212
#define PP_DEC_214 213
#define PP_DEC_215 214
#define PP_DEC_216 215
#define PP_DEC_217 216
#define PP_DEC_218 217
#define PP_DEC_219 218
#define PP_DEC_220 219
#define PP_DEC_221 220
#define PP_DEC_222 221
#define PP_DEC_223 222
#define PP_DEC_224 223
#define PP_DEC_225 224
#define PP_DEC_226 225
#define PP_DEC_227 226
#define PP_DEC_228 227
#define PP_DEC_229 228
#define PP_DEC_230 229
#define PP_DEC_231 230
#define PP_DEC_232 231
#define PP_DEC_233 232
#define PP_DEC_234 233
#define PP_DEC_235 234
#define PP_DEC_236 235
#define PP_DEC_237 236
#define PP_DEC_238 237
#define PP_DEC_239 238
#define PP_DEC_240 239
#define PP_DEC_241 240
#define PP_DEC_242 241
#define PP_DEC_243 242
#define PP_DEC_244 243
#define PP_DEC_245 244
#define PP_DEC_246 245
#define PP_DEC_247 246
#define PP_DEC_248 247
#define PP_DEC_249 248
#define PP_DEC_250 249
#define PP_DEC_251 250
#define PP_DEC_252 251
#define PP_DEC_253 252
#define PP_DEC_254 253
#define PP_DEC_255 254
#define PP_DEC_256 255

// bool conversion
#define PP_BOOL_3 1
#define PP_BOOL_4 1
#define PP_BOOL_5 1
#define PP_BOOL_6 1
#define PP_BOOL_7 1
#define PP_BOOL_8 1
#define PP_BOOL_9 1
#define PP_BOOL_10 1
#define PP_BOOL_11 1
#define PP_BOOL_12 1
#define PP_BOOL_13 1
#define PP_BOOL_14 1
#define PP_BOOL_15 1
#define PP_BOOL_16 1
#define PP_BOOL_17 1
#define PP_BOOL_18 1
#define PP_BOOL_19 1
#define PP_BOOL_20 1
#define PP_BOOL_21 1
#define PP_BOOL_22 1
#define PP_BOOL_23 1
#define PP_BOOL_24 1
#define PP_BOOL_25 1
#define PP_BOOL_26 1
#define PP_BOOL_27 1
#define PP_BOOL_28 1
#define PP_BOOL_29 1
#define PP_BOOL_30 1
#define PP_BOOL_31 1
#define PP_BOOL_32 1
#define PP_BOOL_33 1
#define PP_BOOL_34 1
#define PP_BOOL_35 1
#define PP_BOOL_36 1
#define PP_BOOL_37 1
#define PP_BOOL_38 1
#define PP_BOOL_39 1
#define PP_BOOL_40 1
#define PP_BOOL_41 1
#define PP_BOOL_42 1
#define PP_BOOL_43 1
#define PP_BOOL_44 1
#define PP_BOOL_45 1
#define PP_BOOL_46 1
#define PP_BOOL_47 1
#define PP_BOOL_48 1
#define PP_BOOL_49 1
#define PP_BOOL_50 1
#define PP_BOOL_51 1
#define PP_BOOL_52 1
#define PP_BOOL_53 1
#define PP_BOOL_54 1
#define PP_BOOL_55 1
#define PP_BOOL_56 1
#define PP_BOOL_57 1
#define PP_BOOL_58 1
#define PP_BOOL_59 1
#define PP_BOOL_60 1
#define PP_BOOL_61 1
#define PP_BOOL_62 1
#define PP_BOOL_63 1
#define PP_BOOL_64 1
#define PP_BOOL_65 1
#define PP_BOOL_66 1
#define PP_BOOL_67 1
#define PP_BOOL_68 1
#define PP_BOOL_69 1
#define PP_BOOL_70 1
#define PP_BOOL_71 1
#define PP_BOOL_72 1
#define PP_BOOL_73 1
#define PP_BOOL_74 1
#define PP_BOOL_75 1
#define PP_BOOL_76 1
#define PP_BOOL_77 1
#define PP_BOOL_78 1
#define PP_BOOL_79 1
#define PP_BOOL_80 1
#define PP_BOOL_81 1
#define PP_BOOL_82 1
#define PP_BOOL_83 1
#define PP_BOOL_84 1
#define PP_BOOL_85 1
#define PP_BOOL_86 1
#define PP_BOOL_87 1
#define PP_BOOL_88 1
#define PP_BOOL_89 1
#define PP_BOOL_90 1
#define PP_BOOL_91 1
#define PP_BOOL_92 1
#define PP_BOOL_93 1
#define PP_BOOL_94 1
#define PP_BOOL_95 1
#define PP_BOOL_96 1
#define PP_BOOL_97 1
#define PP_BOOL_98 1
#define PP_BOOL_99 1
#define PP_BOOL_100 1
#define PP_BOOL_101 1
#define PP_BOOL_102 1
#define PP_BOOL_103 1
#define PP_BOOL_104 1
#define PP_BOOL_105 1
#define PP_BOOL_106 1
#define PP_BOOL_107 1
#define PP_BOOL_108 1
#define PP_BOOL_109 1
#define PP_BOOL_110 1
#define PP_BOOL_111 1
#define PP_BOOL_112 1
#define PP_BOOL_113 1
#define PP_BOOL_114 1
#define PP_BOOL_115 1
#define PP_BOOL_116 1
#define PP_BOOL_117 1
#define PP_BOOL_118 1
#define PP_BOOL_119 1
#define PP_BOOL_120 1
#define PP_BOOL_121 1
#define PP_BOOL_122 1
#define PP_BOOL_123 1
#define PP_BOOL_124 1
#define PP_BOOL_125 1
#define PP_BOOL_126 1
#define PP_BOOL_127 1
#define PP_BOOL_128 1
#define PP_BOOL_129 1
#define PP_BOOL_130 1
#define PP_BOOL_131 1
#define PP_BOOL_132 1
#define PP_BOOL_133 1
#define PP_BOOL_134 1
#define PP_BOOL_135 1
#define PP_BOOL_136 1
#define PP_BOOL_137 1
#define PP_BOOL_138 1
#define PP_BOOL_139 1
#define PP_BOOL_140 1
#define PP_BOOL_141 1
#define PP_BOOL_142 1
#define PP_BOOL_143 1
#define PP_BOOL_144 1
#define PP_BOOL_145 1
#define PP_BOOL_146 1
#define PP_BOOL_147 1
#define PP_BOOL_148 1
#define PP_BOOL_149 1
#define PP_BOOL_150 1
#define PP_BOOL_151 1
#define PP_BOOL_152 1
#define PP_BOOL_153 1
#define PP_BOOL_154 1
#define PP_BOOL_155 1
#define PP_BOOL_156 1
#define PP_BOOL_157 1
#define PP_BOOL_158 1
#define PP_BOOL_159 1
#define PP_BOOL_160 1
#define PP_BOOL_161 1
#define PP_BOOL_162 1
#define PP_BOOL_163 1
#define PP_BOOL_164 1
#define PP_BOOL_165 1
#define PP_BOOL_166 1
#define PP_BOOL_167 1
#define PP_BOOL_168 1
#define PP_BOOL_169 1
#define PP_BOOL_170 1
#define PP_BOOL_171 1
#define PP_BOOL_172 1
#define PP_BOOL_173 1
#define PP_BOOL_174 1
#define PP_BOOL_175 1
#define PP_BOOL_176 1
#define PP_BOOL_177 1
#define PP_BOOL_178 1
#define PP_BOOL_179 1
#define PP_BOOL_180 1
#define PP_BOOL_181 1
#define PP_BOOL_182 1
#define PP_BOOL_183 1
#define PP_BOOL_184 1
#define PP_BOOL_185 1
#define PP_BOOL_186 1
#define PP_BOOL_187 1
#define PP_BOOL_188 1
#define PP_BOOL_189 1
#define PP_BOOL_190 1
#define PP_BOOL_191 1
#define PP_BOOL_192 1
#define PP_BOOL_193 1
#define PP_BOOL_194 1
#define PP_BOOL_195 1
#define PP_BOOL_196 1
#define PP_BOOL_197 1
#define PP_BOOL_198 1
#define PP_BOOL_199 1
#define PP_BOOL_200 1
#define PP_BOOL_201 1
#define PP_BOOL_202 1
#define PP_BOOL_203 1
#define PP_BOOL_204 1
#define PP_BOOL_205 1
#define PP_BOOL_206 1
#define PP_BOOL_207 1
#define PP_BOOL_208 1
#define PP_BOOL_209 1
#define PP_BOOL_210 1
#define PP_BOOL_211 1
#define PP_BOOL_212 1
#define PP_BOOL_213 1
#define PP_BOOL_214 1
#define PP_BOOL_215 1
#define PP_BOOL_216 1
#define PP_BOOL_217 1
#define PP_BOOL_218 1
#define PP_BOOL_219 1
#define PP_BOOL_220 1
#define PP_BOOL_221 1
#define PP_BOOL_222 1
#define PP_BOOL_223 1
#define PP_BOOL_224 1
#define PP_BOOL_225 1
#define PP_BOOL_226 1
#define PP_BOOL_227 1
#define PP_BOOL_228 1
#define PP_BOOL_229 1
#define PP_BOOL_230 1
#define PP_BOOL_231 1
#define PP_BOOL_232 1
#define PP_BOOL_233 1
#define PP_BOOL_234 1
#define PP_BOOL_235 1
#define PP_BOOL_236 1
#define PP_BOOL_237 1
#define PP_BOOL_238 1
#define PP_BOOL_239 1
#define PP_BOOL_240 1
#define PP_BOOL_241 1
#define PP_BOOL_242 1
#define PP_BOOL_243 1
#define PP_BOOL_244 1
#define PP_BOOL_245 1
#define PP_BOOL_246 1
#define PP_BOOL_247 1
#define PP_BOOL_248 1
#define PP_BOOL_249 1
#define PP_BOOL_250 1
#define PP_BOOL_251 1
#define PP_BOOL_252 1
#define PP_BOOL_253 1
#define PP_BOOL_254 1
#define PP_BOOL_255 1


#endif //NCUBE_PP_MACROS_H
