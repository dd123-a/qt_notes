//
// Created by DrTang on 2023/12/23.
//

#ifndef NOTES_CONFIG_H
#define NOTES_CONFIG_H

#pragma once

#include <QHash>
#include <QMutex>
#include <QString>
#include <QStringList>
#include <QThread>
#include <QVariant>
#include <QVector>

namespace Medo{class Config;}

class Config{
public:
    //充值配置，包括缓存数据
    static void reset();

    /*! 强制重新加载配置文件。如果文件存在，则返回true。 */
    static bool load();

    /*! 强制立即保存配置文件。如果操作成功，则返回true。 */
    static bool save();

    /*! 强制立即保存配置文件，并在退出前清理一切。 */
    static void quit();
    /* 判断程序是否为便携式，即需要相关的库和配置文件在同一目录，则不是便携式程序*/
    static bool isPortable();

    /*设置是否为便携式，使配置文件和数据目录路径缓存失效*/
    static void setPortable(bool portable);

    /*写入配置时是否自动保存，默默人为true*/
    static bool immediateSave();

    /*! 设置是否写入配置时执行自动保存。
     * \param saveImmediately 如果为true，任何写入将导致立即保存。 */
    static void setImmediateSave(bool saveImmediately);

    /*! 返回配置文件路径。如果文件不存在，将创建它。返回值已缓存。 */
    static QString configurationFile();

    /*! 返回配置文件路径。返回值已缓存。
     * 安装时：
     *   Linux：文件保存在配置目录下（例如~/.config/<appname>.conf）。
     *   Windows：文件保存在应用程序数据路径下（例如C:/Users/<UserName>/AppData/Roaming/<OrgName>/<AppName>/<AppName>.cfg）。
     * 便携式时（未安装或配置文件存在）：
     *   Linux：使用当前目录下的配置文件（例如./.<appname>）。
     *   Windows：使用当前目录下的配置文件（例如./<AppName>.cfg）。 */
    static QString configurationFilePath();


    /*! 设置配置文件路径。不验证路径是否适用于目的。
     * \param configurationFilePath 配置文件的完整路径。 */
     static void setConfigurationFilePath(QString configurationFilePath);

     /*! 返回状态文件路径。如果文件不存在，将创建它。返回值已缓存。 */
     static QString stateFile();

     /*! 返回状态文件路径。返回值已缓存。
     * 安装时：
     *   Linux：文件保存在配置目录下（例如~/.config/<appname>.user）。
     *   Windows：文件保存在应用程序数据路径下（例如C:/Users/<UserName>/AppData/Roaming/<OrgName>/<AppName>/<AppName>.user）。
     * 便携式时（未安装或配置文件存在）：
     *   Linux：使用当前目录下的配置文件（例如./.<appname>.user）。
     *   Windows：使用当前目录下的配置文件（例如./<AppName>.user）。 */
     static QString stateFilePath();

     /*! 设置状态文件路径。不验证路径是否适用于目的。
     * \param stateFilePath 状态文件的完整路径。 */
     static void setStateFilePath(QString stateFilePath);

     /*! 返回数据目录路径。如果目录不存在，将创建它。返回值已缓存。 */
     static QString dataDirectory();

     /*! 返回数据目录路径。返回值已缓存。
     * 安装时：
     *   Linux：数据将保存在本地共享目录中（例如~/.local/share/<appname>）。
     *   Windows：数据将保存在应用程序数据路径的子目录中（例如C:/Users/<UserName>/AppData/Roaming/<OrgName>/<AppName>/Data/）。
     * 便携式时（未安装或配置文件存在）：
     *   Linux：使用当前目录下的子目录（例如./.<appname>.data）。
     *   Windows：使用当前目录下的子目录（例如./<AppName>.Data/）。 */
     static QString dataDirectoryPath();

     /*! 设置数据目录路径。不验证路径是否适用于目的。
     * \param dataDirectoryPath 数据目录的完整路径。 */
     static void setDataDirectoryPath(QString dataDirectoryPath);

     /*! 返回给定键的值，如果未找到，则返回空的QString。
    * /param key 键。 */
     static QString read(QString key)

     /*! 返回给定键的值，如果未找到，则返回默认值。
    * /param key 键。
    * /param defaultValue 默认值。 */
     static QString read(QString key, QString defaultValue);

     /*! 将值写入给定键。
     * /param key 键。
     * /param value 值。 */
     static void write(QString key, QString value);

     /*! 返回给定键的值，如果未找到，则返回默认值。
    * /param key 键。
    * /param defaultValue 默认值。 */
     static QString read(QString key, const char* defaultValue);

     /*! 将值写入给定键。
     * /param key 键。
     * /param value 值。 */
     static void write(QString key, const char* value);

     /*! 返回给定键的值，如果未找到或无法转换为bool，则返回默认值。
     * /param key 键。
     * /param defaultValue 默认值。 */
     static bool read(QString key, bool defaultValue)

     /*! 将值写入给定键。
     * /param key 键。
     * /param value 值。 */
     static void write(QString key, bool value);

     /*! 返回给定键的值，如果未找到或无法转换为int，则返回默认值。
     * /param key 键。
     * /param defaultValue 默认值。 */
     static int read(QString key, int defaultValue);

     /*! 将值写入给定键。
     * /param key 键。
     * /param value 值。 */
     static void write(QString key, int value);

     /*! 返回给定键的值，如果未找到或无法转换为long，则返回默认值。
     * /param key 键。
     * /param defaultValue 默认值。 */
     static long long read(QString key, long long defaultValue);

     /*! 将值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void write(QString key, long long value);

     /*! 返回给定键的值，如果未找到或无法转换为double，则返回默认值。
      * /param key 键。
      * /param defaultValue 默认值。 */
     static double read(QString key, double defaultValue);

     /*! 将值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void write(QString key, double value);

     /*! 返回给定键的所有值，如果键不存在，则返回空列表。
     * /param key 键。 */
     static QStringList readMany(QString key);

     /*! 返回给定键的所有值，如果键不存在，则返回默认值。
      * /param key 键。
      * /param defaultValues 默认值。 */
     static QStringList readMany(QString key, QStringList defaultValues);

     /*! 将值写入给定键。
      * /param key 键。
      * /param values 值。 */
     static void writeMany(QString key, QStringList values);


     /*! 删除给定键的所有值。
     * /param key 键。 */
     static void remove(QString key);

     /*! 删除所有值。 */
     static void removeAll();

     /*! 返回给定键的状态值，如果未找到，则返回默认值。
     * /param key 键。
     * /param defaultValue 默认值。 */
     static QString stateRead(QString key, QString defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, QString value);

     /*! 返回给定键的状态值，如果未找到，则返回默认值。
      * /param key 键。
      * /param defaultValue 默认值。 */
     static QString stateRead(QString key, const char* defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, const char* value);

     /*! 返回给定键的状态值，如果未找到或无法转换为bool，则返回默认值。
     * /param key 键。
     * /param defaultValue 默认值。 */
     static bool stateRead(QString key, bool defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, bool value);

     /*! 返回给定键的状态值，如果未找到或无法转换为int，则返回默认值。
      * /param key 键。
      * /param defaultValue 默认值。 */
     static int stateRead(QString key, int defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, int value);

     /*! 返回给定键的状态值，如果未找到或无法转换为long，则返回默认值。
      * /param key 键。
      * /param defaultValue 默认值。 */
     static long long stateRead(QString key, long long defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, long long value);

     /*! 返回给定键的状态值，如果未找到或无法转换为double，则返回默认值。
      * /param key 键。
      * /param defaultValue 默认值。 */
     static double stateRead(QString key, double defaultValue);

     /*! 将状态值写入给定键。
      * /param key 键。
      * /param value 值。 */
     static void stateWrite(QString key, double value);


     /*! 返回给定键的所有状态值，如果键不存在，则返回空列表。
      * /param key 键。 */
     static QStringList stateReadMany(QString key);

     /*! 返回给定键的所有状态值，如果键不存在，则返回空列表。
      * /param key 键。 */
     static QStringList stateReadMany(QString key, QStringList defaultValues);

     /*! 将状态值写入给定键。
       * /param key 键。 */
     static void stateWriteMany(QString key, QStringList values);

private:
    enum class PortableStatus{
        Unkonw=-1,
        False=0,
        True=1,
    };

private:
    //确保多线程环境下对公共资源的访问没有冲突
    static QMutex _publicAccessMutex;
    /*配置文件路径、状态文件路径和数据目录路径*/
    static QString _configurationFilePath;
    static QString _stateFilePath;
    static QString _dataDirectoryPath;
    /*是否处于便携模式*/
    static PortableStatus _isPortable;
    /*写入配置时是否立即保存*/
    static bool _immediateSave;
    /*返回在便携模式和安装模式下的配置文件路径*/
    static QString configurationFilePathWhenPortable();
    static QString configurationFilePathWhenInstalled();
    //    便携模式和安装模式下的状态文件路径
    static QString stateFilePathWhenPortable();
    static QString stateFilePathWhenInstalled();
    /*便携模式和安装模式下的数据文件路径*/
    static QString dataDirectoryPathWhenPortable();
    static QString dataDirectoryPathWhenInstalled();


private:
    class ConfigFile{
    public:
        /*文件种类，文件路径*/
        ConfigFile(QString kind,QString filePath);
        ~ConfigFile();
        /*保存配置文件*/
        bool save();
        /*请求保存*/
        void requestSave();
        /*读取单个键值对*/
        QString readOne(QString key);
        QStringList readMany(QString key);
        void writeOne(QString key, QString value);
        void writeMany(QString key, QStringList value);
        void removeMany(QString key);
        void removeAll();

    private:
        QMutex _cacheMutex;
        QMutex _saveMutex;
        QHash<QString,QVariant> _cache;

    private:
        class BackgroundSaveThread:private QThread{
        public:
            explicit BackgroundSaveThread(ConfigFile* config);
            ~BackgroundSaveThread();

        public:
            void requestSave();
            void cancelRequestedSave();

        public:
            BackgroundSaveThread(const BackgroundSaveThread&)=delete;
            void operator=(const BackgroundSaveThread&)=delete;

        private:
            ConfigFile* _config= nullptr;
            QMutex _syncRoot;
            bool _saveRequested=false;
            void run();
        };
        Config::ConfigFile::BackgroundSaveThread* _backgroundSaveThread= nullptr;

    private:
        /*文字编辑状态*/
        enum class ProcessState {
            Default,            // 默认状态
            Comment,            // 注释状态
            Key,                // 键的状态
            KeyEscape,          // 键的转义状态
            KeyEscapeLong,      // 键的长转义状态
            SeparatorOrValue,   // 分隔符或值的状态
            ValueOrWhitespace,  // 值或空白字符的状态
            Value,              // 值的状态
            ValueEscape,        // 值的转义状态
            ValueEscapeLong,    // 值的长转义状态
            ValueOrComment      // 值或注释的状态
        };

    private:
        class LineData{
        public:
            LineData();
            LineData(LineData* lineTemplate,QString key,QString value);
            LineData(QString key,QString separatorPrefix,QString separator,QString separatorSuffix,QString value,QString commentPrefix,QString  comment);

        public:
            QString getKey();
            QString getValue();
            void setValue(QString newValue);
            QString toString();
            static void escapeIntoStringBuilder(QString* sb,)

        };

    };





























};













#endif //NOTES_CONFIG_H
