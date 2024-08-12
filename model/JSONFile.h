#ifndef MODEL_JSON_FILE_H
#define MODEL_JSON_FILE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include "AbstractSensor.h"

class JSONFile {
    private:
        std::string path;
        QJsonDocument document;
        bool hasUnsavedChanges;
    public:
        JSONFile();
        JSONFile(const std::string& absolute_path);
        //static JSONFile fromPath(const std::string& absolute_path);
        const std::string& getPath() const;
        void setPath(const std::string&);
        QJsonObject getObject() const;
        QJsonArray getArray() const;
        void store(const std::vector<AbstractSensor*> items);
        std::vector<AbstractSensor*> load() const;
        void add(const AbstractSensor& item);
        void modify(const AbstractSensor& item);
        void remove(const AbstractSensor& item);
        void erase();
        bool hasNotBeenSaved() const;
        void save();
        void save_as(const std::string& absolute_path);
        //void set(const std::string& key, const std::string& value);
        //std::string get(const std::string& key);
};

#endif